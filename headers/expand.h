/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:23:46 by fberthou          #+#    #+#             */
/*   Updated: 2024/08/01 07:01:21 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "includes.h"

// main/utils.c
int		ft_perror(char *err_message);
void	free_tab(t_table *tab, int start);

// parsing/expand_utils.c
int		count_sign(char *str, char sign);
// int		cut_str(char **token, int start, int end);

// parsing/parsing_utils.c
int		include_char(char *token, char c, int start);

// parsing/expand_utils_nd
int		join_str(char **token, int start, int end, char *var_content);
// int		include_exitcode(char **token, int last_exit);

// parsing/getenv.c
int		ft_getenv(char *word, char **env, char **var_content);

#endif
