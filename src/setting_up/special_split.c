/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:16:07 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/12 15:57:09 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*my_malloc_word(const char *s, int len)
{
	char	*word;

	safe_malloc_null(sizeof(char) * (len + 1), (void **)&word);
	if (word == NULL)
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

	new_array = ft_realloc(array, sizeof(char *) * (*c),
			sizeof(char *) * (*c + 1));
	if (new_array == NULL)
		return (handle_memory_failure(array, *c));
	array = new_array;
	array[*c] = my_malloc_word(word_start, len);
	if (array[*c] == NULL)
		return (handle_memory_failure(array, *c));
	(*c)++;
	return (array);
}

static char	**process_split(const char *s, char delimiter, char **array, int *c)
{
	int		i;
	int		start;
	int		quote;

	i = 0;
	start = 0;
	quote = 0;
	while (s[i] != '\0')
	{
		while (s[i] == delimiter && quote == 0)
			i++;
		start = i;
		while (s[i] != '\0' && !is_delimiter(s[i], quote, delimiter))
		{
			if (s[i] == '\'')
				quote = !quote;
			i++;
		}
		array = add_word(array, s + start, i - start, c);
	}
	return (array);
}

char	**special_split(const char *s, char delimiter)
{
	char	**array;
	int		count;

	count = 0;
	array = NULL;
	array = process_split(s, delimiter, array, &count);
	if (array == NULL)
		return (NULL);
	array = ft_realloc(array, sizeof(char *)
			* count, sizeof(char *) * (count + 1));
	if (array == NULL)
		return (handle_memory_failure(array, count));
	array[count] = NULL;
	return (array);
}
