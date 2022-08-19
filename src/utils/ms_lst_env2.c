/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:54:23 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/19 14:47:57 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lst_env	*ls_env_contains_name(t_lst_env **lst, char *str)
{
	t_lst_env	*temp;
	char		*name;

	name = get_env_name(str);
	temp = *(lst);
	while (temp)
	{
		if (!(ft_strncmp(name, temp->name, ft_strlen(name) + 1)))
		{
			free(name);
			return (temp);
		}
		temp = temp->next;
	}
	free(name);
	return (NULL);
}

char	**lst_env_to_strarray(t_lst_env **lst)
{
	t_lst_env	*temp;
	char		**arr;
	int			i;

	if (!(*lst))
		return (NULL);
	arr = malloc(sizeof(char *) * (ls_env_len(lst) + 1));
	i = 0;
	temp = *lst;
	while (temp)
	{
		if (temp->value)
			arr[i++] = ft_strthreejoin(temp->name, "=", temp->value);
		else
			arr[i++] = ft_strdup(temp->name);
		temp = temp->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	ls_env_len(t_lst_env **lst)
{
	t_lst_env	*temp;
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
