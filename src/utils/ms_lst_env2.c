/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:54:23 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/13 10:47:22 by lschrafs         ###   ########.fr       */
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
