/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:26:45 by fberthou          #+#    #+#             */
/*   Updated: 2024/07/27 14:30:42 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"

// ####### PROTOTYPES ######## //

// main/utils.c
int		ft_perror(char *err_message);
void	free_tab(t_table *tab, int start);

// parsing/quote_management.c
int 	quote_management(t_table args, t_table tmp, int y);

// parsing/parsing_utils.c
int     include_char(char *token, char c, int start);

// ####### PROTOTYPES ######## //

static int	clean_token(t_table args, t_table tmp, int i)
{
	if (include_char(args.tab[i], '\'', 0)  >= 0 || \
        include_char(args.tab[i], '\"', 0)  >= 0)
		return (quote_management(args, tmp, i));
	else
	{
		tmp.tab[tmp.size] = ft_strdup(args.tab[i]);
		if (!tmp.tab[tmp.size])
			return (-1);
	}
	return (0);
}

int	token_cleaner(t_data *data)
{
	int		ret_value;
    int     i;
	t_table	tmp;

	tmp.tab = ft_calloc(sizeof(char *), data->args.size + 1);
	if (!tmp.tab)
		return (ft_perror("error-> cleaner tab alloc\n"), -1);
	tmp.size = 0;
    i = 0;
	while (i < data->args.size)
	{
		ret_value = clean_token(data->args, tmp, i);
		if (ret_value == -1 || ret_value == 1)
			return (free_tab(&tmp, 0), 1);
        if (!tmp.tab[tmp.size][0])
            free(tmp.tab[tmp.size]);
		else
            (tmp.size)++;
        i++;
	}
	free_tab(&(data->args), 0);
	data->args = tmp;
	return (0);
}
