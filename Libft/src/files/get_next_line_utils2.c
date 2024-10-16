/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 06:56:10 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/16 06:56:19 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*read_from_fd(int fd, char *buffer, int *bytes_read)
{
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read < 0)
	{
		*bytes_read = 0;
		while (*bytes_read < BUFFER_SIZE)
			buffer[(*bytes_read)++] = 0;
		return (NULL);
	}
	buffer[*bytes_read] = '\0';
	return (buffer);
}
