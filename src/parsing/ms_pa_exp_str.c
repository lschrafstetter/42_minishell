/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pa_exp_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:08:49 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/16 13:45:43 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	len_to_endofvar(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_whitespace(str[i]) && str[i] != '\'' && str[i] != '"')
		i++;
	return (i);
}

static int	index_next_dollar_or_end(const char *str)
{
	int	i;
	int	sq_open;
	int	dq_open;

	sq_open = 0;
	dq_open = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !sq_open)
			return (i);
		if (str[i] == '\'' && !dq_open)
			sq_open = 1 - sq_open;
		if (str[i] == '"' && !sq_open)
			dq_open = 1 - dq_open;
		i++;
	}
	return (i);
}

static void	copy_without_backslashes(char *str1, char *str2)
{
	int	i1;
	int	i2;

	i1 = 0;
	i2 = 0;
	while (str1[i1])
	{
		if (str1[i1] == '\'' || str1[i1] == '"')
		{
			str2[i2] = '\\';
			i2++;
		}
		str2[i2] = str1[i1];
		i2++;
		i1++;
	}
	str2[i2] = 0;
}

static int	expand_dollar(int i, char **expanded, char *str, t_process *proc)
{
	char	*helper[3];
	int		index;
	int		n_quotes;

	i++;
	index = len_to_endofvar(&(str[i]));
	helper[0] = ft_calloc(index + 1, 1);
	ft_strlcat(helper[0], &(str[i]), index + 1);
	if (!strncmp(helper[0], "?", 2))
		helper[1] = ft_itoa(proc->data->exit_code);
	else
		helper[1] = ft_strdup(ms_getenv(proc->data, helper[0]));
	n_quotes = num_quotes_in_env(helper[1]);
	helper[2] = malloc(ft_strlen(helper[1]) + n_quotes + 1);
	copy_without_backslashes(helper[1], helper[2]);
	free(helper[1]);
	free(helper[0]);
	helper[0] = ft_strjoin(*expanded, helper[2]);
	free(*expanded);
	free(helper[2]);
	*expanded = helper[0];
	i += index;
	return (i);
}

void	str_expand(char **str, t_process *process)
{
	int			i;
	int			index;
	char		*expanded;
	char		*helper[2];

	expanded = ft_strdup("");
	i = 0;
	while ((*str)[i])
	{
		index = index_next_dollar_or_end(&((*str)[i]));
		if (index)
		{
			helper[0] = ft_calloc(index + 1, 1);
			ft_strlcat(helper[0], &((*str)[i]), index + 1);
			helper[1] = ft_strjoin(expanded, helper[0]);
			free(expanded);
			free(helper[0]);
			expanded = helper[1];
			i += index;
		}
		else if ((*str)[i] == '$')
			i = expand_dollar(i, &expanded, *str, process);
	}
	free(*str);
	*str = expanded;
}
