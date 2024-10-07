/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:08:02 by mblanc            #+#    #+#             */
/*   Updated: 2024/05/21 13:56:37 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	if (*needle == '\0')
		return ((char *)haystack);
	needle_len = 0;
	while (needle[needle_len] != '\0')
		needle_len++;
	while (*haystack != '\0' && len >= needle_len)
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (i < needle_len && haystack[i] == needle[i])
				i++;
			if (i == needle_len)
				return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}
