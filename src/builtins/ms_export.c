/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:31:01 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/17 09:51:52 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_export_lst(t_process *proc)
{
	t_lst_env	**new;
	t_lst_env	*temp;

	new = copy_env_lst(proc->data->ls_env);
	sort_new_lst(new);
	temp = *new;
	while (temp)
	{
		if (ft_strncmp(temp->name, "_", 2))
		{
			ft_putstr_fd("declare -x ", proc->fdout);
			ft_putstr_fd(temp->name, proc->fdout);
			if (temp->value)
			{
				ft_putstr_fd("=\"", proc->fdout);
				ft_putstr_fd(temp->value, proc->fdout);
				ft_putstr_fd("\"", proc->fdout);
			}
			ft_putstr_fd("\n", proc->fdout);
		}
		temp = temp->next;
	}
	ls_env_clear((new));
	return (0);
}

static void	replace_value(t_lst_env *node, char *str)
{
	free_str(node->value);
	node->value = ft_calloc(ft_strlen(str) + 1, 1);
	ft_strlcat(node->value, str, ft_strlen(str) + 1);
}

int	env_set_value(t_data *data, char *name, char *value)
{
	t_lst_env	*temp;

	if (is_id_invalid(name))
		return (1);
	temp = ls_env_contains_name(data->ls_env, name);
	if (temp)
	{
		if (value)
			replace_value(temp, value);
	}
	else
		ls_env_addback(data->ls_env, ls_env_new(name, value));
	if (data->env)
		free(data->env);
	data->env = lst_env_to_strarray(data->ls_env);
	return (0);
}

int	ms_export(t_process *proc)
{
	int			i;
	int			ret;
	char		*name;
	char		*value;

	i = 1;
	if (!proc->cmd[i])
	{
		print_export_lst(proc);
		return (0);
	}
	while (proc->cmd[i])
	{
		name = get_env_name(proc->cmd[i]);
		value = ft_strchr(proc->cmd[i], '=');
		if (value)
			ret = env_set_value(proc->data, name, value + 1);
		else
			ret = env_set_value(proc->data, name, value);
		free_str(name);
		i++;
	}
	return (ret);
}
