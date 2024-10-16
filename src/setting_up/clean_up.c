/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:35:57 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/16 05:47:48 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanup(t_pipex *pipex, char **cmd, int max_pipes)
{
	int	i;

	i = 0;
	while (i < max_pipes)
	{
		if (pipex->pipes[i])
		{
			close(pipex->pipes[i][0]);
			close(pipex->pipes[i][1]);
			free(pipex->pipes[i]);
		}
		i++;
	}
	free(pipex->pipes);
	pipex->pipes = NULL;
	if (pipex->infile != -1)
		close(pipex->infile);
	if (cmd)
		safe_free_all_strings(&cmd);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->child_pids)
		free(pipex->child_pids);
	if (pipex->cmds)
		free(pipex->cmds);
}
