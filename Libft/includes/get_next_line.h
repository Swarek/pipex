/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:59:56 by mblanc            #+#    #+#             */
/*   Updated: 2024/09/04 14:31:37 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define OPEN_MAX 8192
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*verif_data(char data[BUFFER_SIZE], int fd);
char	*taking_the_buff(int fd, char data[BUFFER_SIZE], char *output);
int		set_data(char data[BUFFER_SIZE], char *output, int bytes_read);

void	*ftt_calloc(size_t num, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
char	*my_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif