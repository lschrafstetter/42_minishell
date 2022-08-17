/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:57:09 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/17 09:32:46 by lschrafs         ###   ########.fr       */
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

int	ms_env(t_process *proc)
{
	t_lst_env	*temp;

	temp = *(proc->data->ls_env);
	while (temp)
	{
		if (temp->value)
		{
			ft_putstr_fd(temp->name, proc->fdout);
			ft_putstr_fd("=", proc->fdout);
			ft_putendl_fd(temp->value, proc->fdout);
		}
		temp = temp->next;
	}
	return (0);
}
