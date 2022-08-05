/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst_str1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:54:23 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/05 18:20:30 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lst_str	*ls_str_new(char *str)
{
	t_lst_str	*new;

	new = malloc(sizeof(t_lst_str));
	new->next = NULL;
	new->str = ft_strdup(str);
	return (new);
}

void	ls_str_addfront(t_lst_str **lst, t_lst_str *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ls_str_addback(t_lst_str **lst, t_lst_str *new)
{
	t_lst_str	*temp;

	if (!(*lst))
	{
		ls_str_addfront(lst, new);
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
}

static void	ls_str_clearnodes(t_lst_str **lst)
{
	if (*lst)
	{
		ls_str_clearnodes(&(*lst)->next);
		if ((*lst)->str)
			free((*lst)->str);
		free(*lst);
		*lst = NULL;
	}
}

void	ls_str_clear(t_lst_str **lst)
{
	if (lst)
		ls_str_clearnodes(lst);
	free(lst);
	lst = NULL;
}
