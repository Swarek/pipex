/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:16:07 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/14 02:02:26 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*my_malloc_word(const char *s, int len)
{
	char	*word;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static char	**handle_memory_failure(char **array, int count)
{
	while (count > 0)
	{
		count--;
		free(array[count]);
	}
	free(array);
	return (NULL);
}

static char	**add_word(char **array, const char *word_start, int len, int *c)
{
	char	**new_array;

	new_array = (char **)ft_realloc(array, sizeof(char *) * (*c),
			sizeof(char *) * (*c + 1));
	if (!new_array)
		return (handle_memory_failure(array, *c));
	array = new_array;
	array[*c] = my_malloc_word(word_start, len);
	if (!array[*c])
		return (handle_memory_failure(array, *c));
	(*c)++;
	return (array);
}

static char	**process_split(const char *s, char delimiter, char **array, int *c)
{
	int	i;
	int	start;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] && s[i] == delimiter && !quote)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && !(s[i] == delimiter && !quote))
		{
			if (s[i] == '\'')
				quote = !quote;
			i++;
		}
		array = add_word(array, s + start, i - start, c);
		if (!array)
			return (NULL);
	}
	return (array);
}

char	**special_split(const char *s, char delimiter)
{
	char	**array;
	int		count;

	if (!s)
		return (NULL);
	count = 0;
	array = NULL;
	array = process_split(s, delimiter, array, &count);
	if (!array)
		return (NULL);
	array = (char **)ft_realloc(array, sizeof(char *) * count,
			sizeof(char *) * (count + 1));
	if (!array)
		return (handle_memory_failure(array, count));
	array[count] = NULL;
	return (array);
}
