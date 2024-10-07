/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:08:10 by mblanc            #+#    #+#             */
/*   Updated: 2024/05/23 23:25:06 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	to_copy;
	size_t	i;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (src_len < dstsize - 1)
		to_copy = src_len;
	else
		to_copy = dstsize - 1;
	if (dstsize != 0)
	{
		i = 0;
		while (i < to_copy)
		{
			dst[i] = src[i];
			i++;
		}
		dst[to_copy] = '\0';
	}
	return (src_len);
}
