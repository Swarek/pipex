/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:55:26 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/17 12:40:00 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*verify_a_path(char *path, char *command)
{
	char	*command_path;
	char	*temp;

	if (!path)
		return (NULL);
	if (path[ft_strlen(path) - 1] != '/')
	{
		temp = ft_strjoin(path, "/");
		if (!temp)
			return (free(path), NULL);
		command_path = ft_strjoin(temp, command);
		free(temp);
	}
	else
		command_path = ft_strjoin(path, command);
	if (command_path == NULL)
		return (free(path), NULL);
	free(path);
	if (access(command_path, X_OK) == 0)
		return (command_path);
	free(command_path);
	return (NULL);
}

static char	*find_command_path(char *command, char **envp)
{
	int		i;
	char	**paths;
	char	*command_path;

	if (!command || *command == '\0' || ft_str_is_whitespace(command))
		return (NULL);
	if (is_absolute_or_relative_path(command))
		return (handle_absolute_or_relative_path(command));
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
		command_path = verify_a_path(ft_strdup(paths[i]), command);
		if (command_path)
			return (safe_free_all_strings(&paths), command_path);
	}
	safe_free_all_strings(&paths);
	return (NULL);
}

static int	are_strings_white_spaces(char **cmd)
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

static char	*prepare_and_find_path(char *argv, char ***cmd, char **envp)
{
	char	*path;

	*cmd = special_split(argv, ' ');
	if (!(*cmd) || are_strings_white_spaces(*cmd) == 1)
	{
		ft_error_msg("Command split failed\n");
		return (NULL);
	}
	*cmd = remove_quotes(*cmd);
	if (!(*cmd) || !(*cmd)[0] || ft_strcmp((*cmd)[0], " ") == 0)
	{
		safe_free_all_strings(cmd);
		ft_error_msg("Empty command\n");
		return (NULL);
	}
	path = find_command_path((*cmd)[0], envp);
	if (!path)
	{
		ft_error_msg("Command not found\n");
		safe_free_all_strings(cmd);
	}
	return (path);
}

int	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	path = prepare_and_find_path(argv, &cmd, envp);
	if (!path)
		return (127);
	i = 0;
	while (cmd[i])
		i++;
	if (execve(path, cmd, envp) == -1)
	{
		if (execute_with_shell(path, cmd, envp, i) == -1)
			return (free(path), safe_free_all_strings(&cmd), 126);
	}
	safe_free_all_strings(&cmd);
	free(path);
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
