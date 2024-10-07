/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:31:33 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/08 17:55:20 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_array(char **array)
{
	int	i;
	int	j;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			write(1, &array[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
