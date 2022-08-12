/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst_str2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:54:23 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/12 11:25:57 by dfranke          ###   ########.fr       */
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

int	is_empty(char* str)
{
	while (*str)
	{
		if (!is_whitespace(*str))
			return(0);
		str++;
	}
	return(1);
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
