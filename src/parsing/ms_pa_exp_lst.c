/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pa_exp_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:13:27 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/06 09:23:55 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	steps_to_relevant_whitespace(char *str)
{
	int	i;
	int	sq_open;
	int	dq_open;

	sq_open = 0;
	dq_open = 0;
	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]) && !sq_open && !dq_open)
			return (i);
		if (str[i] == '\'' && !dq_open)
			sq_open = 1 - sq_open;
		if (str[i] == '"' && !sq_open)
			dq_open = 1 - dq_open;
		i++;
	}
	return (i);
}

static t_lst_str	**split_by_relevant_whitespace(char *str)
{
	t_lst_str	**lst;
	char		*helper;
	int			index;
	int			i;

	lst = malloc(sizeof(t_lst_str **));
	*lst = NULL;
	i = 0;
	while (str[i])
	{
		index = steps_to_relevant_whitespace(&(str[i]));
		if (index)
		{
			helper = ft_calloc(index + 1, 1);
			ft_strlcat(helper, &(str[i]), index + 1);
			ls_str_addback(lst, ls_str_new(helper));
			free(helper);
			i += index;
		}
		else if (str[i])
			i++;
	}
	return (lst);
}

void	expand_list_by_whitespace(t_lst_str **node)
{
	t_lst_str	**temp_lst;
	int			temp_len;

	temp_lst = split_by_relevant_whitespace((*node)->str);
	temp_len = ls_str_len(temp_lst);
	ls_str_getindex(temp_lst, temp_len - 1)->next = (*node)->next;
	free((*node)->str);
	(*node)->str = ft_strdup((*temp_lst)->str);
	(*node)->next = (*temp_lst)->next;
	free((*temp_lst)->str);
	free(*temp_lst);
	free(temp_lst);
}
