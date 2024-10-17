/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:29:19 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/17 13:42:36 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parent_process(t_pipex *pipex, pid_t pid, int cmd_index)
{
	pipex->child_pids[cmd_index] = pid;
	if (cmd_index == 0)
	{
		if (close(pipex->pipes[cmd_index][1]) == -1)
			return (-1);
	}
	else if (cmd_index == pipex->cmd_count - 1)
	{
		if (close(pipex->pipes[cmd_index - 1][0]) == -1)
			return (-1);
	}
	else
	{
		if (close_both(pipex->pipes[cmd_index - 1][0],
			pipex->pipes[cmd_index][1]) == -1)
			return (-1);
	}
	return (0);
}

// This function will call to setup_redirection with dup2
// and call the execute function with the cmd and envp
// It will also close the pipes in the parent process
// This function need as arguments :
// - t_pipex *pipex, with all pipes malloced of len cmd_count -1 and inited,
//			cmd_count, infile, outfile and envp initialized
// - char **argv as : infile cmd1 cmd2 ... cmdN outfile
// - int cmd_index as the index of the command to execute
void	child_process(t_pipex *pipex, int cmd_index)
{
	int	j;

	if (setup_redirection(pipex, cmd_index) == -1)
	{
		cleanup(pipex, NULL, pipex->nbr_pipes);
		ft_error_msg("Redirection failed\n");
		exit(1);
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
	exit (execute(pipex->cmds[cmd_index], pipex->envp));
}

// This function will do all the forks and call the execute_child_process
// It will also close the pipes in the parent process
// This function need as arguments :
// - t_pipex *pipex, with all pipes malloced of len cmd_count -1 and inited,
//			cmd_count, infile, outfile and envp initialized
// - char **argv as : infile cmd1 cmd2 ... cmdN outfile
// - pid_t *child as malloced array of pid_t, of len cmd_count
int	fork_process(t_pipex *pipex)
{
	int		cmd_index;
	pid_t	pid;

	cmd_index = -1;
	while (++cmd_index < pipex->cmd_count)
	{
		pid = fork();
		if (pid < 0)
			return (ft_error_msg("Fork failed\n"), 1);
		if (pid == 0)
			child_process(pipex, cmd_index);
		else
		{
			if (parent_process(pipex, pid, cmd_index) == -1)
				return (ft_error_msg("Parent process failed\n"), 1);
		}
	}
	return (0);
}
