/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:00:03 by fberthou          #+#    #+#             */
/*   Updated: 2024/08/01 20:47:42 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	save_std_fileno(t_data *data, int saved_fd[])
{
	saved_fd[0] = 0;
	saved_fd[1] = 1;
	if (data->input.size > 0)
	{
		saved_fd[0] = dup(STDIN_FILENO);
		if (saved_fd[0] == -1)
			return (perror("ft_save_std infile "), 1);
	}
	if (data->output.size > 0)
	{
		saved_fd[1] = dup(STDOUT_FILENO);
		if (saved_fd[1] == -1)
		{
			if (saved_fd[0] > STDIN_FILENO)
				close(saved_fd[0]);
			return (perror("ft_save_std outfile "), 1);
		}
	}
	return (0);
}

int	redir_file(t_data *data)
{
	if (data->input.size > 0)
	{
		if (dup2(data->in_out_fd[0], STDIN_FILENO) == -1)
			return (perror("redir file infile"), 1);
	}
	if (data->output.size > 0)
	{
		if (dup2(data->in_out_fd[1], STDOUT_FILENO) == -1)
			return (perror("redir file outfile"), 1);
	}
	return (0);
}

int	reset_std_fileno(int saved_fd[])
{
	if (saved_fd[0] > STDIN_FILENO)
	{
		if (dup2(saved_fd[0], STDIN_FILENO) == -1)
		{
			if (saved_fd[1] > STDOUT_FILENO)
				dup2(saved_fd[1], STDOUT_FILENO);
			return (perror("reset in_std "), -1);
		}
	}
	if (saved_fd[1] > STDOUT_FILENO)
	{
		if (dup2(saved_fd[1], STDOUT_FILENO) == -1)
			return (perror("reset outstd "), -1);
	}
	return (0);
}

int	close_all_redir(t_data *data, int saved_std[])
{
	if (saved_std[0] > STDIN_FILENO)
		close(saved_std[0]);
	if (saved_std[1] > STDOUT_FILENO)
		close(saved_std[1]);
	if (data->in_out_fd[0] > STDIN_FILENO)
		close(data->in_out_fd[0]);
	if (data->in_out_fd[1] > STDOUT_FILENO)
		close(data->in_out_fd[1]);
	return (0);
}
