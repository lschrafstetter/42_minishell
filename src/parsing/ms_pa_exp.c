/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pa_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:04 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/05 14:46:14 by lschrafs         ###   ########.fr       */
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
		helper = str_remove_quotes(temp->filename);
		free(temp->filename);
		temp->filename = helper;
		temp = temp->next;
	}
	/*temp = *(process->ls_red);
	while (temp)
	{
		printf("%s\n", temp->filename);
		helper = str_remove_quotes(temp->filename);
		printf("%s\n", helper);
		free(temp->filename);
		temp->filename = helper;
		temp = temp->next;
	}*/
}

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

static void	expand_list_by_whitespace(t_lst_str *node)
{
	t_lst_str	**temp_lst;
	int			temp_len;

	temp_lst = split_by_relevant_whitespace(node->str);
	temp_len = ls_str_len(temp_lst);
	ls_str_getindex(temp_lst, temp_len - 1)->next = node->next;
	free(node->str);
	node->str = ft_strdup((*temp_lst)->str);
	node->next = (*temp_lst)->next;
	free((*temp_lst)->str);
	free(*temp_lst);
	free(temp_lst);
}

static void	expand_sort_cmd(t_process *process)
{
	t_lst_str	*temp;
	char		*helper;

	temp = *(process->ls_cmd);
	while (temp)
	{
		helper = str_expand(temp->str, process);
		free(temp->str);
		temp->str = helper;
		if (contains_relevant_whitespace(temp->str))
			expand_list_by_whitespace(temp);
		helper = str_remove_quotes(temp->str);
		free(temp->str);
		temp->str = helper;
		temp = temp->next;
	}
	/*temp = *(process->ls_cmd);
	while (temp)
	{
		printf("%s\n", temp->str);
		helper = str_remove_quotes(temp->str);
		printf("%s\n", helper);
		free(temp->str);
		temp->str = helper;
		temp = temp->next;
	}*/
}

void	expand_and_sort(t_process *process)
{
	expand_sort_red(process);
	expand_sort_cmd(process);

	printf("Expanding done\n");
	t_lst_red	*temp;
	temp = *(process->ls_red);
	while (temp)
	{
		printf("Red: %s File: %s AG: %i\n", temp->redirection, temp->filename, temp->ambiguous_redirect);
		temp = temp->next;
	}
	t_lst_str	*temp1;
	temp1 = *(process->ls_cmd);
	while (temp1)
	{
		printf("Command: %s\n", temp1->str);
		temp1 = temp1->next;
	}
}
