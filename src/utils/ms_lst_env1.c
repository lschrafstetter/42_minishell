/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst_env1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:54:23 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/13 10:47:19 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lst_env	*ls_env_new(char *name, char *value)
{
	t_lst_env	*new;

	new = malloc(sizeof(t_lst_env));
	new->next = NULL;
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	return (new);
}

void	ls_env_addfront(t_lst_env **lst, t_lst_env *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ls_env_addback(t_lst_env **lst, t_lst_env *new)
{
	t_lst_env	*temp;

	if (!(*lst))
	{
		ls_env_addfront(lst, new);
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
}

static void	ls_env_clearnodes(t_lst_env **lst)
{
	if (*lst)
	{
		ls_env_clearnodes(&(*lst)->next);
		if ((*lst)->name)
			free((*lst)->name);
		if ((*lst)->value)
			free((*lst)->value);
		free(*lst);
		*lst = NULL;
	}
}

void	ls_env_clear(t_lst_env **lst)
{
	if (lst)
		ls_env_clearnodes(lst);
	free(lst);
	lst = NULL;
}
