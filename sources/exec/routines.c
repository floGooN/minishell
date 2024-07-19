/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 08:54:53 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/19 11:10:21 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

int	exec_redirection(t_data data, int *fds, int last_read);

int	child_routine(t_data *data, int tab_size, int i, int **fd)
{
	int	ret_value;

	ret_value = manage_redirection(data, tab_size, i, fd);
	if (ret_value)
		return (ret_value);
	if (is_builtin_child(&data[i]))
		exec_builtin_child(data, tab_size, i, fd);
		
	if (i == tab_size - 1 && fd)
	{
		if (close(fd[i - 1][0]) == -1)
			return (-1);
	}
	else if (fd)
	{
		if (i && close_pipes(fd, (tab_size - 1), i, fd[i - 1][0]) == -1)
			return (-1);
		else if (!i && close_pipes(fd, (tab_size - 1), i, 0) == -1)
			return (-1);
	}
	return (ret_value);
}

int	parent_routine(t_data *data, int i, int tab_size, int **fd)
{
	int	ret_value;

	if (fd)
	{
		if (i == 0)
			ret_value = close(fd[i][1]);
		else
		{
			ret_value = close(fd[i - 1][0]);
			if (i < tab_size - 1)
				ret_value = close(fd[i][1]);
		}
		if (ret_value)
			perror("close pipe in parent ");
	}
	ret_value = close_fds(data[i].in_out_fd);
	if (ret_value == -1)
		perror("close in_out files in parent ");
	return (ret_value);
}
