/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:24:07 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/23 10:34:27 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int save_std(t_data *data, int redir_fd[])
{
    redir_fd[0] = 0;
    redir_fd[1] = 0;
    if (data[0].in_out_fd[0] > STDIN_FILENO)
    {
        redir_fd[0] = dup(STDIN_FILENO);
        if (redir_fd[0] == -1)
            return (perror("ft_save_std infile"), -1);
    }
    if (data[0].in_out_fd[1] > STDOUT_FILENO)
    {
        redir_fd[1] = dup(STDOUT_FILENO);
        if (redir_fd[1] == -1)
        {
            if (redir_fd[0] > STDIN_FILENO)
                dup2(redir_fd[0], STDIN_FILENO);
            return (perror("ft_save_std outfile"), -1);
        }
    }
    return (0);
}

int	close_file(t_data *data, int save_fd[])
{
	if (data[0].in_out_fd[0] > STDIN_FILENO)
	{
		if (close(data[0].in_out_fd[0]) == -1)
			perror("close_file() infile ");
		data[0].in_out_fd[0] = -1;
	}
	if (data[0].in_out_fd[1] > STDOUT_FILENO)
	{
		if (close(data[0].in_out_fd[1]) == -1)
			perror("close_file() outfile ");
		data[0].in_out_fd[1] = -1;
	}
    if (save_fd[0] > STDIN_FILENO)
	{
        dup2(save_fd[0], STDIN_FILENO);
		close(save_fd[0]);
	}
    if (save_fd[1] > STDOUT_FILENO)
	{
        dup2(save_fd[1], STDOUT_FILENO);
		close(save_fd[1]);
	}
    return (data[0].exit_status);
}
