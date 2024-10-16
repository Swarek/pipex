/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 04:42:30 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/16 03:37:47 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// This function redirect the input and output of the command to the pipes
// It will return -1 if the redirection failed
// It takes as arguments :
// - t_pipex *pipex, with all pipes malloced of len cmd_count -1 and inited,
// - int i as the index of the pipe to redirect
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
