/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:34:23 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/13 23:13:54 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5 || envp == NULL)
	{
		ft_error_msg("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
		exit(EXIT_FAILURE);
	}
	if (opening_files(&pipex, argv, argc) == -1)
		exit(EXIT_FAILURE);
	pipex.envp = envp;
	process_pipe(&pipex, argv[2], argv[3]);
	// close(pipex.infile);
	// close(pipex.outfile);
	return (0);
}
