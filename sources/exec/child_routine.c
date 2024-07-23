/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:21:37 by florian           #+#    #+#             */
/*   Updated: 2024/07/23 18:26:50 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void    exec_builtin_child(t_data *data, int i, int **fd, int last_read);
int     manage_redirection(t_data *data, int i, int **fd, int last_read);
int     close_in_out_files(t_data *data);

int child_routine(t_data *data, int i, int **fd, int last_read)
{
    const int tab_size = data[i].tab_size;

    if (is_builtin(&data[i]))
        exec_builtin_child(data, i, fd, last_read);
    manage_redirection(data, i, fd, last_read); // all redir are made no close no free
    close_pipes(fd, data->tab_size - 1, i, last_read);
    while (i < tab_size)
    {
        close_in_out_files(&data[i]);
        i++;
    }
    free_pipes(fd, data->tab_size - 1);
    return (0);
}
