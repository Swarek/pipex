/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_absolute_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:11:50 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/17 12:29:11 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**build_new_cmd(char *path, char **cmd, int cmd_count)
{
	char	**new_cmd;
	int		j;

	new_cmd = malloc(sizeof(char *) * (cmd_count + 2));
	if (!new_cmd)
		return (NULL);
	new_cmd[0] = ft_strdup("/bin/sh");
	new_cmd[1] = ft_strdup(path);
	j = 1;
	while (j < cmd_count)
	{
		new_cmd[j + 1] = ft_strdup(cmd[j]);
		j++;
	}
	new_cmd[cmd_count + 1] = NULL;
	return (new_cmd);
}

int	execute_with_shell(char *path, char **cmd, char **envp, int cmd_count)
{
	char	**new_cmd;
	int		j;

	new_cmd = build_new_cmd(path, cmd, cmd_count);
	if (!new_cmd)
	{
		ft_error_msg("Malloc error\n");
		return (-1);
	}
	if (execve("/bin/sh", new_cmd, envp) == -1)
	{
		j = 0;
		while (new_cmd[j])
		{
			free(new_cmd[j]);
			j++;
		}
		free(new_cmd);
		return (ft_error_msg("Command execution failed\n"));
	}
	return (0);
}

int	is_absolute_or_relative_path(char *command)
{
	if (!command)
		return (0);
	return (command[0] == '/' || (command[0] == '.' && command[1] == '/')
		|| (command[0] == '.' && command[1] == '.' && command[2] == '/'));
}

char	*handle_absolute_or_relative_path(char *command)
{
	if (access(command, X_OK) == 0)
		return (command);
	return (NULL);
}

// char	*handle_absolute_or_relative_path(char *command)
// {
// 	if (access(command, X_OK) == 0)
// 		return (ft_strdup(command));
// 	return (NULL);
// }
