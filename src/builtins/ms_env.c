/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:57:09 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/03 15:43:26 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ms_getenv(t_data *data, char *name)
{
	t_lst_env	*temp;

	temp = *(data->ls_env);
	while (temp)
	{
		if (ft_strncmp(temp->name, name, ft_strlen(name) + 1) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return ("");
}
