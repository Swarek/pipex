/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblanc <mblanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:35:57 by mblanc            #+#    #+#             */
/*   Updated: 2024/10/09 07:29:45 by mblanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void cleanup_parent(t_pipex *pipex)
{
    int i;

    i = 0;
    while (i < pipex->cmd_count - 1)
    {
        if (pipex->pipes[i])
        {
            close(pipex->pipes[i][0]);
            close(pipex->pipes[i][1]);
            free(pipex->pipes[i]);
        }
        i++;
    }
    free(pipex->pipes);
    pipex->pipes = NULL;  // Évite les doubles free

    if (pipex->infile != -1)
        close(pipex->infile);
    if (pipex->outfile != -1)
        close(pipex->outfile);
    if (pipex->child_pids)
        free(pipex->child_pids);
}

void cleanup_child(t_pipex *pipex, char **cmd)
{
    int i;

    // Fermer et libérer les pipes
    i = 0;
    while (i < pipex->cmd_count - 1)
    {
        if (pipex->pipes[i])
        {
            close(pipex->pipes[i][0]);
            close(pipex->pipes[i][1]);
            free(pipex->pipes[i]);
        }
        i++;
    }
    free(pipex->pipes);
    pipex->pipes = NULL;  // Évite les doubles free

    // Fermer infile et outfile
    if (pipex->infile != -1)
        close(pipex->infile);
    if (pipex->outfile != -1)
        close(pipex->outfile);

    // Libérer cmd
    if (cmd)
        safe_free_all_strings(&cmd);

    // Libérer child_pids
    if (pipex->child_pids)  // <-- Ajoutez cette condition ici
    {
        free(pipex->child_pids);
        pipex->child_pids = NULL;  // Éviter un double free plus tard
    }
}
