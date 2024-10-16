/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:55:26 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/16 05:52:26 by mblanc           ###   ########.fr       */
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

	if (!command || *command == '\0' || ft_str_is_whitespace(command))
		return (NULL);
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

int	are_strings_white_spaces(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	*cmd_name(char *cmd)
{
	int		i;
	char	*name;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (ft_error_msg("Memory allocation failed\n"), NULL);
	i = 0;
	while (cmd[i] && cmd[i] != ' ')
	{
		name[i] = cmd[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

int	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = special_split(argv, ' ');
	if (!cmd || are_strings_white_spaces(cmd) == 1)
	{
		ft_error_msg("Command split failed\n");
		return (-1);
	}
	cmd = remove_quotes(cmd);
	if (!cmd || !cmd[0] || ft_strcmp(cmd[0], " ") == 0)
	{
		safe_free_all_strings(&cmd);
		ft_error_msg("Empty command\n");
		return (-1);
	}
	path = find_command_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
	{
		ft_error_msg("Command execution failed\n");
		safe_free_all_strings(&cmd);
		return (-1);
	}
	return (0);
}

// int	execute(char *argv, char **envp)
// {
// 	char	**cmd;
// 	char	*path;

// 	cmd = special_split(argv, ' ');
// 	if (!cmd || are_strings_white_spaces(cmd) == 1)
// 	{
// 		ft_error_msg("Command split failed\n");
// 		return (-1);
// 	}
// 	cmd = remove_quotes(cmd);
// 	if (!cmd || !cmd[0] || ft_strcmp(cmd[0], " ") == 0)
// 	{
// 		safe_free_all_strings(&cmd);
// 		ft_error_msg("Empty command\n");
// 		return (-1);
// 	}
// 	path = find_command_path(cmd[0], envp);
// 	if (!path)
// 	{
// 		ft_error_msg("Command not found\n");
// 		safe_free_all_strings(&cmd);
// 		return (-1);
// 	}
// 	if (execve(path, cmd, envp) == -1)
// 	{
// 		ft_error_msg("Command execution failed\n");
// 		safe_free_all_strings(&cmd);
// 		return (-1);
// 	}
// 	return (0);
// }
