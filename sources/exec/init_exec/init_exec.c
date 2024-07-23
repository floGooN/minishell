/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:15:17 by florian           #+#    #+#             */
/*   Updated: 2024/07/23 16:25:02 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int  init_structure(t_data *data)
{
  int status;

  data->in_out_fd[0] = STDIN_FILENO;
  data->in_out_fd[1] = STDOUT_FILENO;
  if (data->input.size || data->output.size)
  {
    status = handle_redirection(data);
    if (status)
      return (status);
  }
  status = token_cleaner(data);
  if (status == -1 || status == 1)
    return (status);
  return (0);
}

static int  is_executable_path(t_data *data)
{
    if (!data->args.tab)
        return (0);
    if (!ft_strlen(data->args.tab[0]))
        return (0);
    if (data->args.tab[0][0] == '/' || data->args.tab[0][0] == '.')
    {
        data->cmd_path = ft_strdup(data->args.tab[0]);
        if (!data->cmd_path)
            return (-1);
        return (1);
    }
    return (0);
}

static int get_cmd_path(t_data *data)
{
	char	*directory;
    int   ret_value;

    if (!data->args.tab)
        return (1);
    ret_value = is_executable_path(data);
    if (ret_value == -1)
        return (-1);
    if (ret_value == 1)
        return (0);
    directory = NULL;
    ret_value = check_all_dirs(data, &directory);
    if (ret_value)
        return (ret_value);
    if (!directory)
        return (1);
    data->cmd_path = ft_concat_path(directory, data->args.tab[0]);
    free(directory);
    if (!data->cmd_path)
        return (-1);
    return (0);
}

int init_exec(t_data *data, int tab_size)
{
	int ret_value;
	int i;

	if (heredoc_management(data, tab_size) == -1)
			return (-1);
	i = 0;
	while (i < tab_size)
	{
        data[i].tab_size = tab_size;
		ret_value = expand_management(&(data[i]), data[0].env.tab, \
                                        data[0].exit_status);
		if (ret_value)
			return (ret_value);
		ret_value = init_structure(&(data[i]));
		if (ret_value)
			return (ret_value);
		if (!is_builtin(&data[i]))
		{
			ret_value = get_cmd_path(&(data[i]));
			if (ret_value)
				return (ret_value);
		}
		i++;
	}
	return (0);
}
