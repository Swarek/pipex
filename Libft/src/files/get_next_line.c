/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:41:32 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/04 14:31:09 by mblanc           ###   ########.fr       */
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
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			bytes_read = 0;
			while (bytes_read < BUFFER_SIZE)
				data[bytes_read++] = 0;
			return (free(buffer), NULL);
		}
		temp = output;
		output = my_strjoin(output, buffer);
		free(temp);
		free(buffer);
		bytes_read = set_data(data, output, bytes_read);
	}
	return (output);
}

int	set_data(char data[BUFFER_SIZE], char *output, int bytes_read)
{
	int		i;
	int		j;
	char	*memo;

	memo = ft_strchr(output, '\n');
	if (memo == NULL)
		return (bytes_read);
	i = 0;
	j = 1;
	while (memo[j] != '\0')
		data[i++] = memo[j++];
	i = 1;
	while (memo[i])
		memo[i++] = '\0';
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
	char	*memo;
	int		i;

	output = NULL;
	i = -1;
	if (data[0] != 0)
	{
		memo = ft_strchr(data, '\n');
		if (memo)
			return (data_with_nl(data, memo));
		output = ftt_calloc(BUFFER_SIZE + 1, sizeof(char));
		while (data[++i])
			output[i] = data[i];
		i = 0;
		while (i < BUFFER_SIZE)
			data[i++] = 0;
	}
	if (data[0] == 0)
		output = taking_the_buff(fd, data, output);
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
