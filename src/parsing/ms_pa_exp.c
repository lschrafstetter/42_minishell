/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pa_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:04 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/04 16:50:52 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	contains_relevant_whitespace(const char *str)
{
	int	sq_open;
	int	dq_open;

	sq_open = 0;
	dq_open = 0;
	while (*str)
	{
		if (is_whitespace(*str) && !sq_open && !dq_open)
			return (1);
		if (*str == '\'' && !dq_open)
			sq_open = 1 - sq_open;
		if (*str == '"' && !sq_open)
			dq_open = 1 - dq_open;
		str++;
	}
	return (0);
}

static void	expand_sort_red(t_process *process)
{
	t_lst_red	*temp;
	char		*helper;

	temp = *(process->ls_red);
	while (temp)
	{
		helper = str_expand(temp->filename, process);
		free(temp->filename);
		temp->filename = helper;
		if (contains_relevant_whitespace(temp->filename))
			temp->ambiguous_redirect = 1;
		temp = temp->next;
	}
	temp = *(process->ls_red);
	////////////////////
	while (temp)
	{
		printf("Red: %s File: %s AG: %i\n", temp->redirection, temp->filename, temp->ambiguous_redirect);
		temp = temp->next;
	}
	temp = *(process->ls_red);
	
	///////////////////////
	while (temp)
	{
		helper = str_remove_quotes(temp->filename);
		free(temp->filename);
		temp->filename = helper;
		temp = temp->next;
	}
	//////////////////////
	temp = *(process->ls_red);
	while (temp)
	{
		printf("Red: %s File: %s AG: %i\n", temp->redirection, temp->filename, temp->ambiguous_redirect);
		temp = temp->next;
	}
	///////////////////////
	
}

void	expand_and_sort(t_process *process)
{
	expand_sort_red(process);
	//expand_sort_cmd(process);
}
