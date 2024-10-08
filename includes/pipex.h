/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:02:21 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/08 05:12:30 by mblanc           ###   ########.fr       */
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
	int		**pipes;
	int		cmd_count;
	int		infile;
	int		outfile;
	char	**envp;
	int		fd[2];
}	t_pipex;
// Tests

void	execute(char *argv, char **envp);
void	process_pipe(t_pipex *pipex, char *cmd1, char *cmd2);
pid_t	forking(t_pipex *pipex, char *cmd, int fd_in, int fd_out);
int		opening_files(t_pipex *pipex, char **argv, int argc);
void	wait_and_cleanup(t_pipex *pipex, pid_t *child_pids);
void	init_pipes_fork_process(t_pipex *pipex, char **argv, pid_t **child);
void	fork_and_execute_processes(t_pipex *pipex, char **argv, pid_t *child);
void	execute_child_process(t_pipex *pipex, char **argv, int i);
int		setup_redirection(t_pipex *pipex, int i);
void	here_doc_management(char *limiter);

#endif