/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 21:33:35 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/09 21:42:07 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_tlist(t_list *lst)
{
	while (lst != NULL)
	{
		if (lst->content != NULL)
			ft_printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}
