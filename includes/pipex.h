/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:02:21 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/17 12:05:01 by mblanc           ###   ########.fr       */
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
# include <stdio.h>

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

// Leaks, closes and errors
void	wait_and_cleanup(t_pipex *pipex);
int		close_both(int to_close1, int to_close2);
void	cleanup(t_pipex *pipex, char **cmd, int max_pipes);

// Here_doc
int		here_doc_management(char *limiter);
int		handle_here_doc(int *argc, char **argv);

// Processes
int		fork_process(t_pipex *pipex);
void	child_process(t_pipex *pipex, int cmd_index);
int		parent_process(t_pipex *pipex, pid_t pid, int cmd_index);
int		setup_redirection(t_pipex *pipex, int cmd_index);

// Inits
int		init_pipes(t_pipex *pipex);
int		init_child_pids(t_pipex *pipex);
int		init_cmds(t_pipex *pipex, char **av);
int		init_pipex_structure(t_pipex *pipex, char **env, int ac, char **av);
int		all_init(t_pipex *pipex, char **env, int ac, char **av);
int		opening_files(t_pipex *pipex, char **argv, int argc);

// Execution
int		execute(char *argv, char **envp);
int		is_absolute_or_relative_path(char *command);
char	*handle_absolute_or_relative_path(char *command);
int		execute_with_shell(char *path, char **cmd, char **envp, int cmd_count);
char	**remove_quotes(char **cmd);
char	**special_split(const char *s, char delimiter);

// No bonus
pid_t	fork_and_execute(t_pipex *pipex, char *cmd, int fd_in, int fd_out);
void	process_pipe(t_pipex *pipex, char *cmd1, char *cmd2);

#endif