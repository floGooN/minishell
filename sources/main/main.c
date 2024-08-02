/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:58:11 by jedusser          #+#    #+#             */
/*   Updated: 2024/08/01 20:56:32 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_data	*reset_env(t_data *data, int tab_size)
{
	t_table	tmp_env;
	t_table	tmp_export;
	int		last_exit;

	last_exit = data[0].exit_status;
	tmp_env = ft_tabdup(data[0].env.tab);
	if (!tmp_env.tab)
		return (ft_perror("error reset\n"), free_struct(data, tab_size), NULL);
	tmp_export = ft_tabdup(data[0].export.tab);
	if (!tmp_export.tab)
	{
		free_struct(data, tab_size);
		return (ft_perror("error -> reset export\n"), NULL);
	}
	free_struct(data, tab_size);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (free_tab(&tmp_env, 0), free_tab(&tmp_export, 0),
			ft_perror("error -> reset env\n"), NULL);
	init_sighandler(data);
	data[0].env = tmp_env;
	data[0].export = tmp_export;
	data[0].exit_status = last_exit;
	return (data);
}

static t_data	*init_data(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (ft_perror("error -> init structure\n"), NULL);
	if (init_sighandler(data) == -1)
		return (NULL);
	if (!envp || !envp[0])
		data->env = ft_tabdup(create_minimal_env());
	else
		data->env = ft_tabdup(envp);
	if (!data->env.tab)
		return (free(data), ft_perror("error -> init structure\n"), NULL);
	init_exported_env(data);
	if (!data->export.tab)
		return (free(data), ft_perror("error -> init export\n"), NULL);
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		tab_size;

	(void) argv;
	if (argc != 1)
		return (ft_perror("arguments are invalid\n"), 1);
	data = init_data(envp);
	if (!data)
		return (2);
	while (1)
	{
		data->prompt = readline("\033[32mmini$hell>\033[0m ");
		if (!data->prompt)
			return (free_struct(data, 1), exit(EXIT_SUCCESS), 0);
		add_history(data->prompt);
		tab_size = parse_prompt(&data);
		if (tab_size == -1)
			return (free_struct(data, 1), 4);
		if (tab_size > 0)
			exec(tab_size, data);
		data = reset_env(data, data->tab_size);
		if (!data)
			return (5);
	}
	return (0);
}
