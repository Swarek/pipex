/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:51:42 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/08 05:49:57 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	*child_pids;
	int		i;

	if (argc < 5 || envp == NULL)
	{
		ft_error_msg("Usage: ./pipex infile \"cmd1\" \"cmd2\" ... \"cmdn\" outfile\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		here_doc_management(argv[2]);
		argv[1] = "temp.txt";
		i = 2;
		while (argv[i + 1])
		{
			argv[i] = argv[i + 1];
			i++;
		}
		argv[i] = NULL;
		argc--;
	}
	if (opening_files(&pipex, argv, argc) == -1)
		exit(ft_error_msg("Failed to open files\n"));
	pipex.envp = envp;
	pipex.cmd_count = argc - 3;
	init_pipes_fork_process(&pipex, argv, &child_pids);
	wait_and_cleanup(&pipex, child_pids);
	close(pipex.infile);
	close(pipex.outfile);
	return (0);
}
