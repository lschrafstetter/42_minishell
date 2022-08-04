/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:57:09 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/04 17:29:05 by dfranke          ###   ########.fr       */
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

int	env(t_process *proc)
{
	t_lst_env	*temp;

	temp = *(proc->data->ls_env);
	while (temp)
	{
		if (temp->value)
		{
			write (proc->fdout, temp->name, ft_strlen(temp->name));
			write (proc->fdout, temp->value, ft_strlen(temp->value));
			write (proc->fdout, "\n", 1);
		}
		temp = temp->next;
	}
	return (0);
}
