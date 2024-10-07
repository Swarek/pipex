/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 04:42:30 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/08 01:52:11 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	setup_redirection(int input_fd, int output_fd)
// {
// 	if (dup2(input_fd, STDIN_FILENO) == -1)
// 		return (-1);
// 	if (dup2(output_fd, STDOUT_FILENO) == -1)
// 		return (-1);
// 	return (0);
// }

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

void	fork_and_execute_processes(t_pipex *pipex, char **argv, pid_t *child)
{
	int		i;
	int		j;
	pid_t	pid;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			exit(ft_error_msg("Fork failed"));
		if (pid == 0)
		{
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
		i++;
	}
}

void	process_pipes(t_pipex *pipex, char **argv)
{
	int		i;
	pid_t	pid;
	pid_t	*child_pids;

	child_pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!child_pids)
		exit(ft_error_msg("Memory allocation failed"));
	safe_malloc(sizeof(int *) * (pipex->cmd_count - 1), (void **)&pipex->pipes);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (safe_malloc(sizeof(int) * 2, (void **)&pipex->pipes[i]) == NULL)
			exit(EXIT_FAILURE);
		if (pipe(pipex->pipes[i]) == -1)
			exit(ft_error_msg("Pipe creation failed"));
		i++;
	}
	fork_and_execute_processes(pipex, argv, child_pids);
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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5 || envp == NULL)
	{
		ft_error_msg("Usage: ./pipex infile \"cmd1\" \"cmd2\" ... \"cmdn\" outfile\n");
		exit(EXIT_FAILURE);
	}
	if (opening_files(&pipex, argv, argc) == -1)
		exit(ft_error_msg("Failed to open files\n"));
	pipex.envp = envp;
	pipex.cmd_count = argc - 3;
	process_pipes(&pipex, argv);
	close(pipex.infile);
	close(pipex.outfile);
	return (0);
}
