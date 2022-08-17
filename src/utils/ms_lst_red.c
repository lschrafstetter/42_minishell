/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:54:23 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/17 10:01:58 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lst_red	*ls_red_new(char *redirection, char *filename)
{
	t_lst_red	*new;

	new = malloc(sizeof(t_lst_red));
	new->next = NULL;
	new->red = ft_strdup(redirection);
	new->file = ft_strdup(filename);
	new->ambiguous_redirect = 0;
	return (new);
}

void	ls_red_addfront(t_lst_red **lst, t_lst_red *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ls_red_addback(t_lst_red **lst, t_lst_red *new)
{
	t_lst_red	*temp;

	if (!(*lst))
	{
		ls_red_addfront(lst, new);
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
}

static void	ls_red_clearnodes(t_lst_red **lst)
{
	if (*lst)
	{
		ls_red_clearnodes(&(*lst)->next);
		if ((*lst)->red)
			free((*lst)->red);
		if ((*lst)->file)
			free((*lst)->file);
		free(*lst);
		*lst = NULL;
	}
}

void	ls_red_clear(t_lst_red **lst)
{
	if (lst)
		ls_red_clearnodes(lst);
	free(lst);
	lst = NULL;
}
