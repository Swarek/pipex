/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:03:46 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/09 05:21:49 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*safe_malloc_exit(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "Memory allocation failed\n", 25);
		exit(EXIT_FAILURE);
	}
	ft_memset(ptr, 0, size);
	return (ptr);
}

void	*safe_malloc_null(size_t size, void **ptr)
{
	if (!ptr)
		return (NULL);
	*ptr = malloc(size);
	if (!(*ptr))
	{
		ft_error_msg("Memory allocation failed\n");
		return (NULL);
	}
	ft_memset(*ptr, 0, size);
	return (*ptr);
}
