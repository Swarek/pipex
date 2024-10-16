/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:02:21 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/16 18:04:43 by mblanc           ###   ########.fr       */
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
#include <stdio.h>

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
	int		nbr_pipes;
	int		infile;
	int		outfile;
	char	**envp;
	int		fd[2];
	char	**cmds;
	pid_t	*child_pids;
}	t_pipex;

// Functions

int		execute(char *argv, char **envp);
void	process_pipe(t_pipex *pipex, char *cmd1, char *cmd2);
pid_t	fork_and_execute(t_pipex *pipex, char *cmd, int fd_in, int fd_out);
int		opening_files(t_pipex *pipex, char **argv, int argc);
void	wait_and_cleanup(t_pipex *pipex);
int		init_pipes_fork_process(t_pipex *pipex, char **argv, pid_t **child);
int		fork_and_execute_processes(t_pipex *pipex, char **argv, pid_t *child);
int		execute_child_process(t_pipex *pipex, char **argv, int i);
int		setup_redirection(t_pipex *pipex, int i);
int		here_doc_management(char *limiter);
char	**special_split(const char *s, char c);
void	cleanup_parent(t_pipex *pipex);
void	cleanup_child(t_pipex *pipex, char **cmd, int max_pipes);
int		is_delimiter(char c, int quote, char delimiter);
void	close_both(int to_close1, int to_close2);
char	**remove_quotes(char **cmd);
char	*find_command_path(char *command, char **envp);
int		handle_here_doc(int *argc, char **argv);
int		all_init(t_pipex *pipex, char **env, int ac, char **av);
void	cleanup(t_pipex *pipex, char **cmd, int max_pipes);
int		fork_process(t_pipex *pipex);
char	*handle_absolute_or_relative_path(char *command);
int		is_absolute_or_relative_path(char *command);
int		execute_with_shell(char *path, char **cmd, char **envp, int cmd_count);

#endif