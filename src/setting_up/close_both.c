/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_both.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:45:05 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/17 13:23:47 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_both(int to_close1, int to_close2)
{
	if (close(to_close1) == -1)
		return (-1);
	if (close(to_close2) == -1)
		return (-1);
	return (0);
}
