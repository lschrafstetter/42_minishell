/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pa_exp_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:08:49 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/04 16:26:36 by lschrafs         ###   ########.fr       */
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

static int	expand_dollar(int i, char **expanded, char *str, t_process *proc)
{
	char	*helper1;
	char	*helper2;
	int		index;

	i++;
	index = len_to_endofvar(&(str[i]));
	helper1 = ft_calloc(index + 1, 1);
	ft_strlcat(helper1, &(str[i]), index + 1);
	helper2 = ms_getenv(proc->data, helper1);
	free(helper1);
	helper1 = ft_strjoin(*expanded, helper2);
	free(*expanded);
	*expanded = helper1;
	i += index;
	return (i);
}

char	*str_expand(char *str, t_process *process)
{
	int			i;
	int			index;
	char		*expanded;
	char		*helper1;
	char		*helper2;

	expanded = ft_strdup("");
	i = 0;
	while (str[i])
	{
		index = index_next_dollar_or_end(&(str[i]));
		if (index)
		{
			helper1 = ft_calloc(index + 1, 1);
			ft_strlcat(helper1, &(str[i]), index + 1);
			helper2 = ft_strjoin(expanded, helper1);
			free(expanded);
			free(helper1);
			expanded = helper2;
			i += index;
		}
		else if (str[i] == '$')
			i = expand_dollar(i, &expanded, str, process);
	}
	return (expanded);
}
