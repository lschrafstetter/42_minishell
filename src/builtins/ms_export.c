/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:31:01 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/04 17:25:37 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*env_var_value(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	while (str[i] || str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	while (str[i])
	{
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

t_lst_env	*copy_env_lst(t_lst_env *env)
{
	t_lst_env	*new;
	t_lst_env	*temp;

	temp = env;
	new = malloc(sizeof(t_lst_env **));
	if (!(new))
		return ;
	new = NULL;
	while (temp)
	{
		ls_env_addback(new, (ls_env_new(temp->name, temp->value)));
		temp = temp->next;
	}
	return (new);
}

int	sort_new_lst(t_lst_env *new)
{
	t_lst_env	*temp;
	t_lst_env	*temp1;

	temp = new;
	temp1 = new;
	while (temp)
	{
		while (temp1)
			if (strncmp(temp1->name, )
	}
}

/* sorting is the next step */

int		print_export_lst(t_process *proc)
{
	t_lst_env	*new;
	char		prefix;

	prefix = strdup("declare -x ");
	new = copy_env_lst(proc->data->ls_env);
	sort_new_lst(new);
	return (0);
}

int	export(t_process *proc)
{
	t_lst_env	*temp;
	int			i;

	i = 1;
	if (!proc->cmd[i])
	{
		print_export_lst(proc);
		return (0);
	}
	while (proc->cmd[i])
	{
		ls_env_addback(proc->data->ls_env, \
				(ls_env_new(get_env_name(proc->cmd[i]), \
				env_var_value(proc->cmd[i]))));
		i++;
	}
	return (0);
}

/*
Export alone sorts the entries of the env list and puts the values in double 
quotes.

1. add OLDPWD as NAME to new linked list
2. oversee _=/usr/bin/env
	- format the strings correctly, (add quotations & "declare -x ")
	- declare -x EXAMPLE="this is example"
3. Sort the list in the correct order (CAPITALS - underscore - lowercase)
*/