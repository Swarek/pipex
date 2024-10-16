/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:55:50 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/16 18:14:30 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*remove_outer_quotes(char *str)
{
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	if (str[0] == '\'' && str[len - 1] == '\'' && len > 1)
	{
		tmp = ft_substr(str, 1, len - 2);
		if (!tmp)
			return (NULL);
		free(str);
		return (tmp);
	}
	return (str);
}

char	**remove_quotes(char **cmd)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = remove_outer_quotes(cmd[i]);
		if (!cmd[i])
			return (NULL);
		len = ft_strlen(cmd[i]);
		j = 0;
		i++;
	}
	return (cmd);
}
