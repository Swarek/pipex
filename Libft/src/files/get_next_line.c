/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:41:32 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/16 06:55:58 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*taking_the_buff(int fd, char data[BUFFER_SIZE], char *output)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		buffer = ftt_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (free(output), NULL);
		if (!read_from_fd(fd, buffer, &bytes_read))
		{
			free(buffer);
			return (free(output), NULL);
		}
		temp = output;
		output = my_strjoin(output, buffer);
		free(temp);
		free(buffer);
		if (!output)
			return (NULL);
		bytes_read = set_data(data, output, bytes_read);
	}
	return (output);
}

int	set_data(char data[BUFFER_SIZE], char *output, int bytes_read)
{
	int		i;
	int		j;
	char	*memo;

	if (!output)
		return (bytes_read);
	memo = ft_strchr(output, '\n');
	if (memo == NULL)
		return (bytes_read);
	i = 0;
	j = 1;
	while (memo[j] != '\0' && i < BUFFER_SIZE)
		data[i++] = memo[j++];
	if (i < BUFFER_SIZE)
	{
		i = 1;
		while (memo[i] && i < BUFFER_SIZE)
			memo[i++] = '\0';
	}
	return (0);
}

char	*data_with_nl(char data[BUFFER_SIZE], char *place_sn)
{
	char	*output;
	int		i;
	int		j;

	i = -1;
	j = 0;
	output = ftt_calloc(place_sn - data + 2, sizeof(char));
	while (data[++i] != '\n')
		output[i] = data[i];
	output[i] = '\n';
	output[++i] = '\0';
	while (data[i] != '\0')
		data[j++] = data[i++];
	while (data[j])
		data[j++] = '\0';
	return (output);
}

char	*verif_data(char data[BUFFER_SIZE], int fd)
{
	char	*output;

	output = process_data(data);
	if (output)
		return (output);
	if (data[0] == 0)
	{
		output = taking_the_buff(fd, data, output);
		if (!output)
			return (NULL);
	}
	return (output);
}

char	*get_next_line(int fd)
{
	static char	data[BUFFER_SIZE + 1];
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		while (i < BUFFER_SIZE)
			data[i++] = 0;
		return (NULL);
	}
	return (verif_data(data, fd));
}
