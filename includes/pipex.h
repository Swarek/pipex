/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:02:21 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/06 05:54:46 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// Includes
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h> 
// Defines
# define TRUE (int)1
# define FALSE (int)0

# define INT_MAX 2147483647
# define INT_MIN -2147483648

// Structures

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**envp;
	int		fd[2];
}	t_pipex;
// Tests

void	execute(char *argv, char **envp);
void	process_pipe(t_pipex *pipex, char *cmd1, char *cmd2);

#endif