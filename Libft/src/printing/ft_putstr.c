/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:29:31 by mblanc            #+#    #+#             */
/*   Updated: 2024/06/16 19:53:00 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(const char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		write(1, str, 1);
		str++;
		count++;
	}
	return (count);
}
