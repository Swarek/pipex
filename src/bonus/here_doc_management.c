/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 04:54:57 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/16 03:23:35 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h> // Pour perror

void	handle_here_doc(int *argc, char **argv)
{
	int	i;

	here_doc_management(argv[2]);
	argv[1] = "temp.txt";
	i = 2;
	while (argv[i + 1])
	{
		argv[i] = argv[i + 1];
		i++;
	}
	argv[i] = NULL;
	(*argc)--;
}

void	here_doc_management(char *limiter)
{
	size_t	len;
	char	*line;
	int		fd;

	fd = open("temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening temp.txt");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, limiter) == 0 || len == 0)
		{
			free(line);
			break ;
		}
		if (write(fd, line, ft_strlen(line)) == -1)
		{
			perror("Error writing to temp.txt");
			free(line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		if (write(fd, "\n", 1) == -1)
		{
			perror("Error writing newline to temp.txt");
			free(line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		free(line);
	}
	close(fd);
}
