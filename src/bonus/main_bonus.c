/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 02:51:42 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/16 06:43:21 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_and_cleanup(t_pipex *pipex)
{
	int	i;
	int	status;
	int	exit_code;

	exit_code = 0;
	i = 0;
	while (i < pipex->cmd_count)
	{
		if (waitpid(pipex->child_pids[i], &status, 0) == -1)
		{
			ft_error_msg("Waitpid failed\n");
			exit_code = 1;
		}
		i++;
	}
	cleanup(pipex, NULL, pipex->nbr_pipes);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	exit(exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5 || envp == NULL)
		return (ft_error_msg("Not enought arguments or envp problem\n"), -1);
	if (ft_strcmp(argv[1], "here_doc") == 0 && argc > 5)
		if (handle_here_doc(&argc, argv) == -1)
			return (-1);
	if (opening_files(&pipex, argv, argc) == -1)
		return (-1);
	if (all_init(&pipex, envp, argc, argv) == -1)
		return (-1);
	fork_process(&pipex);
	wait_and_cleanup(&pipex);
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
