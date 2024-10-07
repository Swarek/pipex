/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:51:50 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/06 19:58:04 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *src, size_t size)
{
	void	*dup;

	if (!src || size == 0)
		return (NULL);
	dup = malloc(size);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, src, size);
	return (dup);
}
