/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:16:07 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/11 00:08:10 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	count_words(const char *str, char c)
// {
// 	int	count;

// 	count = 0;
// 	while (*str)
// 	{
// 		while (*str && *str == c)
// 			str++;
// 		if (*str && *str != c)
// 		{
// 			count++;
// 			while (*str && *str != c)
// 				str++;
// 		}
// 	}
// 	return (count);
// }

// char	*malloc_word(const char *str, char c)
// {
// 	const char	*end;
// 	char		*word;
// 	int			i;

// 	end = str;
// 	while (*end && !*end != c)
// 		end++;
// 	word = malloc(end - str + 1);
// 	if (!word)
// 		return (NULL);
// 	i = 0;
// 	while (str < end)
// 	{
// 		word[i] = *str;
// 		str++;
// 		i++;
// 	}
// 	word[i] = '\0';
// 	return (word);
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		words;
// 	char	**array;
// 	int		i;

// 	words = count_words(s, c);
// 	array = malloc(sizeof(char *) * (words + 1));
// 	if (!array || !s)
// 		return (NULL);
// 	i = 0;
// 	while (i < words)
// 	{
// 		while (*s == c)
// 			s++;
// 		array[i] = malloc_word(s, c);
// 		if (!array[i])
// 		{
// 			while (i-- > 0)
// 				free(array[i]);
// 			return (free(array), NULL);
// 		}
// 		while (*s && *s != c)
// 			s++;
// 		i++;
// 	}
// 	return (array[words] = NULL, array);
// }

char	*my_malloc_word(const char *s, int len)
{
	char	*word;

	safe_malloc_null(sizeof(char) * (len + 1), (void **)&word);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

int	is_between_quotes(const char *s, int pos)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (i < pos)
	{
		if (s[i] == '\'')
		{
			quote = !quote;
		}
		i++;
	}
	return (quote);
}

char	**special_split(const char *s, char c)
{
	int		i;
	int		start;
	int		count;
	char	**array;
	char	**temp;

	i = 0;
	start = 0;
	count = 0;
	array = NULL;
	if (!s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && !is_between_quotes(s, i))
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
		{
			if (s[i] == '\'')
			{
				i++;
				while (s[i] != '\'' && s[i] != '\0')
					i++;
				if (s[i] == '\'')
					i++;
			}
			else
				i++;
		}
		if (i > start)
		{
			count++;
			temp = ft_realloc(array, sizeof(char *) * (count - 1), sizeof(char *) * count);
			if (!temp)
			{
				while (count-- > 1)
					free(array[count - 1]);
				free(array);
				return (NULL);
			}
			array = temp;
			array[count - 1] = my_malloc_word(&s[start], i - start);
			if (!array[count - 1])
			{
				while (count-- > 1)
					free(array[count - 1]);
				free(array);
				return (NULL);
			}
		}
	}
	temp = ft_realloc(array, sizeof(char *) * count, sizeof(char *) * (count + 1));
	if (!temp)
	{
		while (count-- > 0)
			free(array[count]);
		free(array);
		return (NULL);
	}
	array = temp;
	array[count] = NULL;
	return (array);
}
