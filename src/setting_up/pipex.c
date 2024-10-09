/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:19:46 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/09 02:51:22 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	forking(t_pipex *pipex, char *cmd, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_error_msg("Fork failed\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (fd_in != STDIN_FILENO)
			dup2(fd_in, STDIN_FILENO);
		if (fd_out != STDOUT_FILENO)
			dup2(fd_out, STDOUT_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		execute(cmd, pipex->envp);
		ft_error_msg("execve failed\n");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	process_pipe(t_pipex *pipex, char *cmd1, char *cmd2)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipex->fd) == -1)
	{
		ft_error_msg("Pipe creation failed\n");
		exit(EXIT_FAILURE);
	}
	pid1 = forking(pipex, cmd1, pipex->infile, pipex->fd[1]);
	pid2 = forking(pipex, cmd2, pipex->fd[0], pipex->outfile);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	opening_files(t_pipex *pipex, char **argv, int argc)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		return (ft_error_msg("Failed to open infile\n"));
	pipex->outfile = open(argv[argc - 1], O_WRONLY);
	if (pipex->outfile < 0)
		return (ft_error_msg("Failed to open outfile\n"));
}
