/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:40:05 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/04 13:43:42 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	char	buffer[12];
	int		len;
	int		count;

	count = 0;
	len = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		ft_putchar('-');
		count++;
	}
	ft_itoa_base(n, buffer, &len);
	count += len;
	while (len > 0)
		ft_putchar(buffer[--len]);
	return (count);
}
