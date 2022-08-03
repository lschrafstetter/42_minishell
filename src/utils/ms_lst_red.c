/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:54:23 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/03 16:17:03 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lst_red	*ls_red_new(char *redirection, char *filename)
{
	t_lst_red	*new;

	new = malloc(sizeof(t_lst_red));
	new->next = NULL;
	new->redirection = ft_strdup(redirection);
	new->filename = ft_strdup(filename);
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
		if ((*lst)->redirection)
			free((*lst)->redirection);
		if ((*lst)->filename)
			free((*lst)->filename);
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
