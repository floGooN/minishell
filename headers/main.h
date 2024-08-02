/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:03:18 by fberthou          #+#    #+#             */
/*   Updated: 2024/08/01 20:52:45 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "exec.h"
# include "includes.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include "struct.h"

int				ft_perror(char *err_message);
int				init_sighandler(t_data *data);
int				parse_prompt(t_data **data);
void			free_struct(t_data *struc, int tab_size);
void			free_tab(t_table *tab, int start);
void			exec(int tab_size, t_data *data);
int				ft_getenv(char *word, char **env, char **var_content);
t_table			ft_tabdup(char **envp);
int				init_exported_env(t_data *data);

#endif