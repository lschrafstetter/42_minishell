/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pa_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:04 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/16 14:46:06 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	contains_relevant_whitespace(const char *str)
{
	int	sq_open;
	int	dq_open;
	int	i;

	sq_open = 0;
	dq_open = 0;
	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]) && !sq_open && !dq_open)
			return (1);
		if (str[i] == '\'' && !dq_open)
			sq_open = 1 - sq_open;
		if (str[i] == '"' && !sq_open)
			dq_open = 1 - dq_open;
		i++;
	}
	return (0);
}

static void	expand_sort_red(t_process *process)
{
	t_lst_red	*temp;

	temp = *(process->ls_red);
	while (temp)
	{
		str_expand(&(temp->file), process);
		if (contains_relevant_whitespace(temp->file))
			temp->ambiguous_redirect = 1;
		str_remove_quotes(&(temp->file));
		remove_backslashes_before_quotes(&(temp->file));
		temp = temp->next;
	}
}

static void	expand_sort_cmd(t_process *process)
{
	t_lst_str	*temp;

	temp = *(process->ls_cmd);
	while (temp)
	{
		str_expand(&(temp->str), process);
		if (contains_relevant_whitespace(temp->str))
			expand_list_by_whitespace(&temp);
		str_remove_quotes(&(temp->str));
		remove_backslashes_before_quotes(&(temp->str));
		temp = temp->next;
	}
	process->cmd = lst_str_to_strarray(process->ls_cmd);
	ls_str_clear(process->ls_cmd);
	process->ls_cmd = NULL;
}

void	expand_and_sort(t_process *process)
{
	expand_sort_red(process);
	expand_sort_cmd(process);
}
