/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 04:42:30 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/12 23:40:30 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	execute_child_process(t_pipex *pipex, char **argv, int i)
{
	int	j;

	if (setup_redirection(pipex, i) == -1)
	{
		ft_error_msg("Redirection failed\n");
		cleanup_child(pipex, NULL, pipex->cmd_count - 1);
		return (-1);
	}
	j = 0;
	while (j < pipex->cmd_count - 1)
	{
		close(pipex->pipes[j][0]);
		close(pipex->pipes[j][1]);
		j++;
	}
	close(pipex->infile);
	close(pipex->outfile);
	if (execute(argv[2 + i], pipex->envp) == -1)
	{
		cleanup_child(pipex, NULL, pipex->cmd_count - 1);
		return (-1);
	}
	return (0);
}

int	fork_and_execute_processes(t_pipex *pipex, char **argv, pid_t *child)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < pipex->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			return (ft_error_msg("Fork failed\n"));
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
				close_both(pipex->pipes[i - 1][0], pipex->pipes[i][1]);
		}
	}
	return (0);
}

int	init_pipes(t_pipex *pipex)
{
	int	i;

	safe_malloc_null(sizeof(int *) * (pipex->cmd_count - 1),
		(void **)&pipex->pipes);
	if (!pipex->pipes)
		return (ft_error_msg("Memory allocation failed\n"));
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		safe_malloc_null(sizeof(int) * 2, (void **)&pipex->pipes[i]);
		if (!pipex->pipes[i])
		{
			cleanup_child(pipex, NULL, i);
			cleanup_parent(pipex);
			return (ft_error_msg("Memory allocation failed\n"));
		}
		if (pipe(pipex->pipes[i]) == -1)
		{
			cleanup_child(pipex, NULL, i);
			cleanup_parent(pipex);
			return (ft_error_msg("Pipe creation failed\n"));
		}
		i++;
	}
	return (0);
}

int	init_pipes_fork_process(t_pipex *pipex, char **argv, pid_t **child)
{
	safe_malloc_null(sizeof(pid_t) * pipex->cmd_count, (void **)child);
	if (!*child)
		return (ft_error_msg("Memory allocation failed\n"));
	pipex->child_pids = *child;
	if (init_pipes(pipex) == -1)
		return (-1);
	fork_and_execute_processes(pipex, argv, *child);
	return (0);
}
