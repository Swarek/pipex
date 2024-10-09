/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 04:54:57 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/09 06:59:28 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_management(char *limiter)
{
	char	*line;
	int		fd;

	fd = open("temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}
