/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:55:26 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/07 02:47:15 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*verify_a_path(char *path, char *command)
{
	char	*command_path;

	if (!path)
		return (NULL);
	command_path = ft_strjoin(path, command);
	if (command_path == NULL)
		return (free(path), NULL);
	free(path);
	if (access(command_path, X_OK) == 0)
		return (command_path);
	free(command_path);
	return (NULL);
}

char	*find_command_path(char *command, char **envp)
{
	int		i;
	char	**paths;
	char	*command_path;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		command_path = verify_a_path(ft_strjoin(paths[i], "/"), command);
		if (command_path)
			return (safe_free_all_strings(&paths), command_path);
	}
	safe_free_all_strings(&paths);
	return (NULL);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = find_command_path(cmd[0], envp);
	if (!path)
	{
		ft_error_msg("Command not found\n");
		safe_free_all_strings(&cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_error_msg("Command not found\n");
		exit(EXIT_FAILURE);
	}
}
