/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:34:18 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/08 17:59:08 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_assert(int condition, const char *msg)
{
	if (!condition && msg)
	{
		while (*msg)
		{
			write(2, msg, 1);
			msg++;
		}
		write(2, "\n", 1);
		exit(1);
	}
}
