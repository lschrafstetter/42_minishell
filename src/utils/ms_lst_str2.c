/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst_str2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:54:23 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/13 10:34:22 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ls_str_len(t_lst_str **lst)
{
	t_lst_str	*temp;
	int			i;

	temp = *lst;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

t_lst_str	*ls_str_getindex(t_lst_str **lst, int index)
{
	t_lst_str	*temp;
	int			i;

	temp = *lst;
	i = 0;
	while (temp)
	{
		if (i == index)
			return (temp);
		i++;
		temp = temp->next;
	}
	return (NULL);
}

static int	is_empty(char *str)
{
	while (*str)
	{
		if (!is_whitespace(*str))
			return (0);
		str++;
	}
	return (1);
}

char	**lst_str_to_strarray(t_lst_str **lst)
{
	t_lst_str	*temp;
	char		**arr;
	int			i;

	arr = malloc(sizeof(char *) * (ls_str_len(lst) + 1));
	i = 0;
	temp = *lst;
	while (temp)
	{
		if (!is_empty(temp->str))
		{
			arr[i] = ft_strdup(temp->str);
			i++;
		}
		temp = temp->next;
	}
	arr[i] = NULL;
	return (arr);
}
