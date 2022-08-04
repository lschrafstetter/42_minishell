/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd_echo_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 09:52:50 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/04 17:24:55 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(t_process *proc)
{
	char *str;

	str = ms_getenv(proc->data, "PWD");
	write(proc->fdout, str, ft_strlen(str));
	write(proc->fdout, "\n", 1);
	return (0);
}

int	echo(t_process *proc)
{
	int i;
	int is_nl;

	i = 1;
	is_nl = 1;
	if (!ft_strncmp(proc->cmd[i], "-n", 3))
	{
		is_nl = 0;
		i++;
	}
	while (proc->cmd[i])
	{
		write(proc->fdout, proc->cmd[i], ft_strlen(proc->cmd[i]));
		if (proc->cmd[i + 1])
			write(proc->fdout, " ", 1);
		i++;
	}
	if (is_nl)
		write(proc->fdout, "\n", 1);
	return (0);
}

void	delete_env(t_process *proc, char *str)
{
	t_lst_env	*temp;
	t_lst_env	*prev;
	int			i;

	i = 0;
	temp = *(proc->data->ls_env);
	while (temp)
	{
		if (!ft_strncmp(temp->name, str, \
				ft_strlen(str + 1)))
		{
			if (i == 0)
				*(proc->data->ls_env) = temp->next;
			else if (i > 0)
				prev->next = temp->next;
			free(temp->name);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
		i++;
	}
}

int	unset(t_process *proc)
{
	int			i;

	i = 1;
	while (proc->cmd[i])
	{
		delete_env(proc, proc->cmd[i]);
		i++;
	}
	return (0);
}
