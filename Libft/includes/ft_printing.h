/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:38:56 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/09 21:42:32 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTING_H
# define FT_PRINTING_H

# include "libft.h"

void	ft_print_array(char **array);
int		ft_printf(const char *format, ...);
void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);
void	ft_putendl_fd(char *s, int fd);
void	ft_itoa_base(int n, char *buffer, int *len);
int		ft_putnbr_b(unsigned long nbr, char *base);
void	ft_putnbr_fd(int n, int fd);
int		ft_putnbr_unsigned(unsigned long n);
void	ft_putstr_fd(char *str, int fd);
int		ft_putstr(const char *str);
int		ft_putnbr(int n);
void	print_tlist(t_list *lst);

#endif