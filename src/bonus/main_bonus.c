/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:51:42 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/14 17:26:01 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	initialize_pipex(t_pipex *pipex, char **envp)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pipes = NULL;
	pipex->cmd_count = 0;
	pipex->child_pids = NULL;
	pipex->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	*child_pids;
	int		here_doc;

	here_doc = 0;
	child_pids = NULL;
	initialize_pipex(&pipex, envp);
	if (argc < 5 || envp == NULL)
		return (ft_error_msg
			("Usage: ./pipex infile \"cmd1\" \"cmd2\"... \"cmdn\" outfile\n"));
	if (ft_strcmp(argv[1], "here_doc") == 0 && argc > 5)
		handle_here_doc(&argc, argv);
	if (opening_files(&pipex, argv, argc) == -1)
		return (cleanup_parent(&pipex), -1);
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

// ---------------------- TRAINING ---------------------- //
// Fork training
// Goal is to quickly get the sum of a list
// thanks to three proceses (parent, child1, child2)

// int	calcul_sum(char *array, int start, int end)
// {
// 	int	sum;

// 	sum = 0;
// 	while (start < end)
// 		sum += array[start++] - '0';
// 	return (sum);
// }

// void	child_process(char *array, int fd[2], int start, int end)
// {
// 	int	sum;

// 	close(fd[0]);
// 	sum = calcul_sum(array, start, end);
// 	write(fd[1], &sum, sizeof(int));
// 	close(fd[1]);
// 	exit(0);
// }

// int	parent_process(char *array, int fd1[2], int fd2[2], int sum_parent)
// {
// 	int	total_sum;
// 	int	sum_from_child1;
// 	int	sum_from_child2;

// 	total_sum = sum_parent;
// 	ft_printf("\nsum parent : %d\n", sum_parent);
// 	close(fd1[1]);
// 	close(fd2[1]);
// 	read(fd1[0], &sum_from_child1, sizeof(int));
// 	ft_printf("\nsum child 1 : %d\n", sum_from_child1);
// 	read(fd2[0], &sum_from_child2, sizeof(int));
// 	ft_printf("\nsum child 2 : %d\n", sum_from_child2);
// 	total_sum = total_sum + sum_from_child1 + sum_from_child2;
// 	close(fd1[0]);
// 	close(fd2[0]);
// 	return (total_sum);
// }

// int	fork_and_calculate(char *argv, int fd1[2], int fd2[2])
// {
// 	int	id1;
// 	int	id2;
// 	int	len_array;

// 	len_array = ft_strlen(argv);
// 	id1 = fork();
// 	if (id1 == 0)
// 		child_process(argv, fd1, 0, len_array / 3);
// 	id2 = fork();
// 	if (id2 == 0)
// 		child_process(argv, fd2, len_array / 3, (len_array / 3) * 2);
// 	return (parent_process(argv, fd1, fd2,
// 			calcul_sum(argv, (len_array / 3) * 2, len_array)));
// }

// int	main(void)
// {
// 	char	array[] = "123456789";
// 	int		total_sum;
// 	int		fd1[2];
// 	int		fd2[2];

// 	if (pipe(fd1) == -1 || pipe(fd2) == -1)
// 	{
// 		ft_error_msg("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	ft_printf("test");
// 	total_sum = fork_and_calculate(array, fd1, fd2);
// 	ft_printf("\ntotal_sum = %d", total_sum);
// 	return (0);
// }
