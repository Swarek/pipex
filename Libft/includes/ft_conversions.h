/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:37:49 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/06 16:37:50 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONVERSIONS_H
# define FT_CONVERSIONS_H

# include "libft.h"

int		ft_atoi_base(char *str, char *base);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

#endif