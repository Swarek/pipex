/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:51:42 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/09 14:15:17 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Waits for all child processes to finish and cleans up allocated resources.
 *
 * This function waits for each child process to complete using waitpid,
 * then frees the memory allocated for the child PIDs and the pipes.
 *
 * Parameters:
 * - pipex: Pointer to the t_pipex structure containing
 * 			file descriptors and other necessary data.
 * - child_pids: Array of child process PIDs.
 *
 * The function exits if waitpid fails.
 */
void	wait_and_cleanup(t_pipex *pipex, pid_t *child_pids)
{
	int	i;
	int	status;
	int	exit_code;

	exit_code = 0;
	i = 0;
	while (i < pipex->cmd_count)
	{
		if (waitpid(child_pids[i], &status, 0) == -1)
		{
			ft_error_msg("Waitpid failed\n");
			exit_code = 1;
		}
		i++;
	}
	cleanup_parent(pipex);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	exit(exit_code);
}

void	handle_here_doc(int *argc, char **argv)
{
	int	i;

	here_doc_management(argv[2]);
	argv[1] = "temp.txt";
	i = 2;
	while (argv[i + 1])
	{
		argv[i] = argv[i + 1];
		i++;
	}
	argv[i] = NULL;
	(*argc)--;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	*child_pids;
	int		here_doc;

	here_doc = 0;
	child_pids = NULL;
	pipex.infile = -1;
	pipex.outfile = -1;
	pipex.pipes = NULL;
	pipex.cmd_count = 0;
	pipex.child_pids = NULL;
	if (argc < 5 || envp == NULL)
	{
		ft_error_msg("Usage: ./pipex infile \"cmd1\" \"cmd2\" ... \"cmdn\" outfile\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
		handle_here_doc(&argc, argv);
	if (opening_files(&pipex, argv, argc) == -1)
	{
		cleanup_parent(&pipex);
		exit(EXIT_FAILURE);
	}
	pipex.envp = envp;
	pipex.cmd_count = argc - 3;
	if (init_pipes_fork_process(&pipex, argv, &child_pids) == -1)
	{
		cleanup_parent(&pipex);
		exit(EXIT_FAILURE);
	}
	wait_and_cleanup(&pipex, child_pids);
	close(pipex.infile);
	close(pipex.outfile);
	return (0);
}
