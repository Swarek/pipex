/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:06:09 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/16 18:11:20 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->pipes = malloc(sizeof(int *) * (pipex->nbr_pipes));
	if (!pipex->pipes)
		return (ft_error_msg("Memory allocation failed\n"));
	while (i < pipex->nbr_pipes)
	{
		pipex->pipes[i] = malloc(2 * sizeof(int));
		if (!pipex->pipes[i])
		{
			cleanup(pipex, NULL, i);
			return (ft_error_msg("Memory allocation failed\n"));
		}
		if (pipe(pipex->pipes[i]) == -1)
		{
			cleanup(pipex, NULL, i);
			return (ft_error_msg("Pipe creation failed\n"));
		}
		i++;
	}
	return (0);
}

int	init_child_pids(t_pipex *pipex)
{
	pipex->child_pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->child_pids)
	{
		cleanup(pipex, NULL, pipex->nbr_pipes);
		return (ft_error_msg("Memory allocation failed\n"));
	}
	return (0);
}

int	init_cmds(t_pipex *pipex, char **av)
{
	int		i;

	i = 2;
	while (av[i + 1])
	{
		pipex->cmds[i - 2] = av[i];
		i++;
	}
	return (0);
}

int	init_pipex_structure(t_pipex *pipex, char **env, int ac, char **av)
{
	pipex->cmds = malloc(sizeof(char *) * (ac - 3));
	if (!pipex->cmds)
		return (ft_error_msg("Memory allocation failed\n"), -1);
	pipex->pipes = NULL;
	pipex->cmd_count = ac - 3;
	pipex->nbr_pipes = pipex->cmd_count - 1;
	pipex->child_pids = NULL;
	pipex->envp = env;
	if (init_cmds(pipex, av) == -1)
		return (-1);
	return (0);
}

int	all_init(t_pipex *pipex, char **env, int ac, char **av)
{
	if (init_pipex_structure(pipex, env, ac, av) == -1)
		return (-1);
	if (init_pipes(pipex) == -1)
		return (-1);
	if (init_child_pids(pipex) == -1)
		return (-1);
	return (0);
}
