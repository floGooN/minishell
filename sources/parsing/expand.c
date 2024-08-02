/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:27:19 by fberthou          #+#    #+#             */
/*   Updated: 2024/08/01 20:46:24 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>

char		*extract_word(char *str, int start, int end);
int			manage_empty_var(char **token, int i, int i_end);
int			change_value(char **token, int *i, char **envp, int last_exit);

int	find_end_var(char *token, int i)
{
	while (token[i])
	{
		if (token[i] == 9 || token[i] == 32 || token[i] == '\"' || \
			token[i] == '$' || token[i] == '\'' || token[i] == '/')
			return (i);
		i++;
	}
	return (i);
}

int	cut_str(char **token, int start, int end, char *var)
{
	char	*tmp;
	int		i;
	int		y;

	y = 0;
	i = -1;
	tmp = ft_calloc(ft_strlen(*token) + ft_strlen(var) + 1, 1);
	if (!tmp)
		return (ft_perror("error-> alloc cut_str\n"), -1);
	while (++i < start)
		tmp[i] = token[0][i];
	while (var && var[y])
	{
		tmp[i] = var[y++];
		i++;
	}
	while (token[0][end])
	{
		tmp[i] = token[0][end++];
		i++;
	}
	if (var)
		free(var);
	free(token[0]);
	return (token[0] = tmp, 0);
}

int	check_loop(t_table *arg, char **envp, int last_exit, int i_tab)
{
	int	flag;
	int	i;

	i = -1;
	flag = 0;
	while (arg->tab[i_tab] && arg->tab[i_tab][++i])
	{
		if (arg->tab[i_tab][i] == '\'' && flag == 0)
			flag = 1;
		else if (arg->tab[i_tab][i] == '\'' && flag == 1)
			flag = 0;
		else if (arg->tab[i_tab][i] == '\"' && flag == 0)
			flag = -1;
		else if (arg->tab[i_tab][i] == '\"' && flag == -1)
			flag = 0;
		else if (arg->tab[i_tab][i] == '$' && flag <= 0)
		{
			if (change_value(&arg->tab[i_tab], &i, envp, last_exit) == -1)
				return (-1);
			if (arg->tab[i_tab][i] == '$')
				if (change_value(&arg->tab[i_tab], &i, envp, last_exit) == -1)
					return (-1);
		}
	}
	return (0);
}

static int	arg_management(t_table *arg, char **envp, int last_exit)
{
	int	i_tab;

	i_tab = -1;
	while (++i_tab < arg->size)
	{
		if (check_loop(arg, envp, last_exit, i_tab) == -1)
			return (-1);
	}
	return (0);
}

int	expand_management(t_data *data, char **envp, int last_exit)
{
	int	ret_value;

	ret_value = arg_management(&(data->input), envp, last_exit);
	if (ret_value == -1)
		return (-1);
	else if (ret_value == 1)
		return (1);
	ret_value = arg_management(&(data->output), envp, last_exit);
	if (ret_value == -1)
		return (-1);
	else if (ret_value == 1)
		return (1);
	return (arg_management(&(data->args), envp, last_exit));
}
