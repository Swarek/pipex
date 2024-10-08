/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 04:42:30 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/08 05:43:06 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Sets up the input and output redirections for a 
 * 				specific child process in the pipeline.
 *
 * Depending on the position of the process in the
 * 				pipeline (first, middle, or last),
 * this function redirects the standard input and output
 * 						to the appropriate file descriptors.
 *
 * Parameters:
 * - pipex: Pointer to the t_pipex structure containing
 * 				file descriptors and other necessary data.
 * - i: Index of the current command in the pipeline.
 *
 * Returns:
 * - 0 on success.
 * - -1 if an error occurs during redirection.
 */
int	setup_redirection(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1
			|| dup2(pipex->pipes[i][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (i == pipex->cmd_count - 1)
	{
		if (dup2(pipex->pipes[i - 1][0], STDIN_FILENO) == -1
			|| dup2(pipex->outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup2(pipex->pipes[i - 1][0], STDIN_FILENO) == -1
			|| dup2(pipex->pipes[i][1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

/**
 * Executes a child process for a given command in the pipeline.
 *
 * This function is called after a successful  fork in the child process.
 * It sets up the necessary redirections, closes unused file descriptors,
 * and executes the command using execve.
 * If execution fails, it exits the child process.
 *
 * Parameters:
 * - pipex: Pointer to the t_pipex structure containing
 * 				file descriptors and other necessary data.
 * - argv: Array of command-line arguments.
 * - i: Index of the current command in the pipeline.
 *
 * The function does not return; it exits the process upon completion or error.
 */
void	execute_child_process(t_pipex *pipex, char **argv, int i)
{
	int	j;

	if (setup_redirection(pipex, i) == -1)
		exit(ft_error_msg("Redirection failed"));
	j = 0;
	while (j < pipex->cmd_count - 1)
	{
		close(pipex->pipes[j][0]);
		close(pipex->pipes[j][1]);
		j++;
	}
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	execute(argv[2 + i], pipex->envp);
	exit(EXIT_FAILURE);
}

/**
 * Forks child processes for each command in the pipeline
 * and manages file descriptors.
 *
 * This function iterates over each command, forks a child process,
 * and in the child process, calls execute_child_process to handle execution.
 * In the parent process, it closes unnecessary pipe ends and stores
 * the child PIDs for later use.
 *
 * Parameters:
 * - pipex: Pointer to the t_pipex structure containing
 * 			file descriptors and other necessary data.
 * - argv: Array of command-line arguments.
 * - child: Array to store the PIDs of the child processes.
 *
 * The function exits if fork fails.
 */
void	fork_and_execute_processes(t_pipex *pipex, char **argv, pid_t *child)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < pipex->cmd_count)
	{
		ft_printf("TEST1");
		pid = fork();
		ft_printf("TEST2");
		if (pid == -1)
			exit(ft_error_msg("Fork failed"));
		if (pid == 0)
			execute_child_process(pipex, argv, i);
		else
		{
			child[i] = pid;
			if (i == 0)
				close(pipex->pipes[i][1]);
			else if (i == pipex->cmd_count - 1)
				close(pipex->pipes[i - 1][0]);
			else
			{
				close(pipex->pipes[i - 1][0]);
				close(pipex->pipes[i][1]);
			}
		}
	}
}

/**
 * Initializes pipes and forks child processes for pipeline execution.
 *
 * This function allocates memory for the array of child PIDs and the pipes,
 * initializes the pipes, and then calls fork_and_execute_processes to
 * create child processes and execute the commands.
 *
 * Parameters:
 * - pipex: Pointer to the t_pipex structure containing
 * 			file descriptors and other necessary data.
 * - argv: Array of command-line arguments.
 * - child_pids: Double pointer to store the array of child PIDs.
 *
 * The function exits on memory allocation failure or if pipe creation fails.
 */
void	init_pipes_fork_process(t_pipex *pipex, char **argv, pid_t **child)
{
	int		i;

	safe_malloc_null(sizeof(pid_t) * pipex->cmd_count, (void **)child);
	if (!*child)
		exit(ft_error_msg("Memory allocation failed"));
	safe_malloc_null(sizeof(int *) * (pipex->cmd_count - 1),
		(void **)&pipex->pipes);
	if (!*child || !pipex->pipes)
	{
		ft_safe_free((void **)child);
		exit(ft_error_msg("Memory allocation failed"));
	}
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		safe_malloc_null(sizeof(int) * 2, (void **)&pipex->pipes[i]);
		if (!pipex->pipes[i])
			exit(ft_error_msg("Memory allocation failed"));
		if (pipe(pipex->pipes[i]) == -1)
			exit(ft_error_msg("Pipe creation failed"));
		i++;
	}
	fork_and_execute_processes(pipex, argv, *child);
}

/*
 * Waits for all child processes to finish and cleans up allocated resources.
 *
 * This function waits for each child process to complete using waitpid,
 * then frees the memory allocated for the child PIDs and the pipes.
 *
 * Parameters:
 * - pipex: Pointer to the t_pipex structure containing
 * 			file descriptors and other necessary data.
 * - child_pids: Array of child process PIDs.
 *
 * The function exits if waitpid fails.
 */
void	wait_and_cleanup(t_pipex *pipex, pid_t *child_pids)
{
	int		i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		if (waitpid(child_pids[i], NULL, 0) == -1)
			exit(ft_error_msg("Waitpid failed"));
		i++;
	}
	free(child_pids);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
}
