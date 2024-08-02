/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:07:06 by fberthou          #+#    #+#             */
/*   Updated: 2024/08/01 20:46:06 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include <stdbool.h>

// main/utils.c
int			ft_perror(char *err_message);
// parsing/parsing_utils.c
char		*final_build(char *token, char c);

char	*init_new_str(char *token, int nb_char)
{
	if (nb_char % 2)
		return (ft_perror("error -> syntax\n"), NULL);
	if (!nb_char)
		return (ft_strdup(token));
	return (ft_calloc(ft_strlen(token) + 1, sizeof(char)));
}

int	capture_the_flag(char *token, int *i, int *flag)
{
	if (token[*i] == '\"' && *flag == 0)
	{
		*flag = -1;
		(*i)++;
		return (1);
	}
	else if (token[*i] == '\"' && *flag == -1)
	{
		*flag = 0;
		(*i)++;
		return (capture_the_flag(token, i, flag));
	}
	else if (token[*i] == '\'' && *flag == 0)
	{
		*flag = 1;
		(*i)++;
		return (1);
	}
	else if (token[*i] == '\'' && *flag == 1)
	{
		*flag = 0;
		(*i)++;
		return (capture_the_flag(token, i, flag));
	}
	return (0);
}

int	delete_char(char *token, t_table *tmp)
{
	int	flag;
	int	y;
	int	i;

	i = 0;
	y = -1;
	flag = 0;
	while (i < (int)ft_strlen(token) && token[i])
	{
		capture_the_flag(token, &i, &flag);
		if (flag == -1 && token[i] != '\"')
			tmp->tab[tmp->size][++y] = token[i++];
		if (flag == 1 && token[i] != '\'')
			tmp->tab[tmp->size][++y] = token[i++];
		if (flag == 0)
			tmp->tab[tmp->size][++y] = token[i++];
		capture_the_flag(token, &i, &flag);
	}
	if (flag != 0)
		return (ft_perror("error -> unexpected token\n"), -1);
	return (0);
}

int	quote_management(t_table args, t_table *tmp)
{
	tmp->tab[tmp->size] = ft_calloc(ft_strlen(args.tab[tmp->size]) + 1, 1);
	if (!tmp->tab[tmp->size])
		return (ft_perror("alloc -> quote_management"), -1);
	return (delete_char(args.tab[tmp->size], tmp));
}
