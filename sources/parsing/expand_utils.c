/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:10:11 by fberthou          #+#    #+#             */
/*   Updated: 2024/08/01 20:10:13 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <expand.h>

int		cut_str(char **token, int start, int end, char *var);
int		find_end_var(char *token, int i);

char	*extract_word(char *str, int start, int end)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_calloc((end - start) + 1, sizeof(char));
	if (!tmp)
		return (ft_perror("error-> alloc extract word\n"), NULL);
	while (start < end)
	{
		tmp[i] = str[start];
		i++;
		start++;
	}
	return (tmp);
}

int	count_sign(char *str, char sign)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == sign)
		i++;
	return (i);
}

int	manage_empty_var(char **token, int i, int i_end)
{
	char	*var_content;
	int		flag;
	int		y;

	y = 0;
	flag = 0;
	while (y <= i)
	{
		if (token[0][y] == '\'' && flag == 0)
			flag = 1;
		else if (token[0][y] == '\'' && flag == 1)
			flag = 0;
		else if (token[0][y] == '\"' && flag == 0)
			flag = -1;
		else if (token[0][y] == '\"' && flag == 1)
			flag = 0;
		y++;
	}
	if (flag)
	{
		var_content = ft_calloc(2, 1);
		var_content[0] = '$';
		return (cut_str(token, i, i_end, var_content));
	}
	return (cut_str(token, i, i_end, NULL));
}

int	change_value(char **token, int *i, char **envp, int last_exit)
{
	char	*word;
	char	*var_content;
	int		i_end;
	int		y;

	y = 0;
	i_end = find_end_var(*token, *i + 1);
	word = extract_word(*token, *i + 1, i_end);
	if (!word)
		return (-1);
	if (ft_strncmp(word, "?", ft_strlen(word)) == 0)
		return (free(word), cut_str(token, *i, i_end, ft_itoa(last_exit)));
	if (!word[0])
		return (free(word), manage_empty_var(token, *i, i_end));
	if (ft_getenv(word, envp, &var_content) == -1)
		return (free(word), -1);
	free(word);
	if (!var_content)
		return (cut_str(token, *i, i_end, NULL));
	return (cut_str(token, *i, i_end, var_content));
}
