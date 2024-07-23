/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:00:59 by florian           #+#    #+#             */
/*   Updated: 2024/07/23 19:36:31 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int     manage_redirection(t_data *data, int i, int **fd, int last_read);
int     close_in_out_files(t_data *data);

void exec_builtin_child(t_data *data, int i, int **fd, int last_read)
{
    int exit_status;
    int tab_size;

    tab_size = data[i].tab_size;
    manage_redirection(data, i, fd, last_read);
    if (i < tab_size - 1)
    {
        if (close(fd[i][0]) == -1)
            perror("close read pipe in exec_builtin_child() ");
        fd[i][0] = -1;
    }
    exit_status = exec_builtin(data, tab_size, i, fd);
    close_pipes(fd, tab_size - 1, i, last_read);
    while (i < tab_size)
    {
        close_in_out_files(&data[i]);
        i++;
    }
    free_pipes(fd, data->tab_size - 1);
    free_struct(data, tab_size);
    exit(exit_status);
}
