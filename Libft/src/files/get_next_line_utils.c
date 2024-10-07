/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:43:10 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/04 14:32:36 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

void	*ftt_calloc(size_t num, size_t size)
{
	void	*output;
	char	*initializing_chain;
	size_t	i;
	size_t	total_size;

	total_size = num * size;
	output = malloc(total_size);
	if (!output && total_size == 0)
		return (NULL);
	initializing_chain = (char *)output;
	i = 0;
	while (i < total_size)
		initializing_chain[i++] = 0;
	return (output);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (char *)dest;
	s = (const char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

char	*my_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = 0;
	len2 = 0;
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	result = ftt_calloc(len1 + len2 + 1, sizeof(char));
	if (result != NULL)
	{
		ft_memcpy(result, s1, len1);
		ft_memcpy(result + len1, s2, len2);
		result[len1 + len2] = '\0';
	}
	return (result);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	const char	*temp;
	char		*dup;
	size_t		len;
	size_t		i;

	if (!s)
		return (NULL);
	temp = s;
	len = 0;
	i = 0;
	if (s[0] == '\0')
		return (NULL);
	while (*temp++)
		len++;
	dup = (char *)malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
