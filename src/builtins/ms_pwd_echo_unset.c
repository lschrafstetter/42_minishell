/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd_echo_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 09:52:50 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/17 14:07:45 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_pwd(t_process *proc)
{
	char	*str;

	str = ms_getenv(proc->data, "PWD");
	ft_putendl_fd(str, proc->fdout);
	return (0);
}

int	ms_echo(t_process *proc)
{
	int	i;
	int	is_nl;

	if (!proc->cmd[1])
		return (print_return_error("\n", 0, proc->fdout));
	i = 1;
	is_nl = 1;
	if (!ft_strncmp(proc->cmd[i], "-n", 3))
	{
		is_nl = 0;
		i++;
	}
	while (proc->cmd[i])
	{
		ft_putstr_fd(proc->cmd[i], proc->fdout);
		if (proc->cmd[i + 1])
			ft_putstr_fd(" ", proc->fdout);
		i++;
	}
	if (is_nl)
		write(proc->fdout, "\n", 1);
	return (0);
}

static void	delete_env(t_process *proc, char *str)
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

int	ms_unset(t_process *proc)
{
	int	i;

	i = 1;
	while (proc->cmd[i])
	{
		delete_env(proc, proc->cmd[i]);
		i++;
	}
	if (proc->data->env)
		free_strarray(proc->data->env);
	proc->data->env = lst_env_to_strarray(proc->data->ls_env);
	return (0);
}
