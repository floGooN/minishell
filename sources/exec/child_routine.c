/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:21:37 by florian           #+#    #+#             */
/*   Updated: 2024/07/23 17:10:05 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void    exec_builtin_child(t_data *data, int i, int **fd, int last_read);
int     manage_redirection(t_data *data, int i, int **fd, int last_read);

int child_routine(t_data *data, int i, int **fd, int last_read)
{
    int ret_value = 0;

    if (is_builtin(&data[i]))
        exec_builtin_child(data, i, fd, last_read);

    manage_redirection(data, i, fd, last_read); // all redir are made no close no free
    close_pipes(fd, data->tab_size - 1, i, last_read);
    free_pipes(fd, data->tab_size - 1);
	return (ret_value);
}
