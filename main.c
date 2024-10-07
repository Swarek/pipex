/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:34:23 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/07 02:56:41 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	opening_files(t_pipex *pipex, char **argv)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		return (ft_error_msg("Failed to open infile\n"));
	pipex->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		return(ft_error_msg("Failed to open outfile\n"));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5 || envp == NULL)
	{
		ft_error_msg("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
		exit(EXIT_FAILURE);
	}
	if (opening_files(&pipex, argv) == -1)
		exit(EXIT_FAILURE);
	pipex.envp = envp;
	process_pipe(&pipex, argv[2], argv[3]);
	close(pipex.infile);
	close(pipex.outfile);
	return (0);
}

// Main for BONUS
// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	pipex;
// 	int		i;
// 	int		fd_in;

// 	if (argc < 5 || envp == NULL)
// 	{
// 		ft_error_msg("Invalid arguments\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	opening_files(&pipex, argv);
// 	pipex.envp = envp;
// 	fd_in = pipex.infile;
// 	i = 2;
// 	while (i < argc - 2)
// 	{
// 		if (pipe(pipex.fd) == -1)
// 			ft_error_msg("Pipe creation failed\n");
// 		process_pipe(&pipex, argv[i], argv[i + 1]);
// 		close(pipex.fd[1]);
// 		fd_in = pipex.fd[0];
// 		i++;
// 	}
// 	process_pipe(&pipex, argv[argc - 2], NULL);
// 	close(pipex.infile);
// 	close(pipex.outfile);
// 	return (0);
// }