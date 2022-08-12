/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:14:53 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/12 13:14:51 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lst_env	**copy_env_lst(t_lst_env **env)
{
	t_lst_env	**new;
	t_lst_env	*temp;

	temp = *env;
	new = malloc(sizeof(t_lst_env **));
	if (!new)
		return (NULL);
	*new = NULL;
	while (temp)
	{
		ls_env_addback(new, (ls_env_new(temp->name, temp->value)));
		temp = temp->next;
	}
	return (new);
}

void	swap(t_lst_env *node, t_lst_env *node2)
{
	char	*temp_value;
	char	*temp_name;

	temp_name = node->name;
	temp_value = node->value;
	node->name = node2->name;
	node->value = node2->value;
	node2->name = temp_name;
	node2->value = temp_value;
}

void	sort_new_lst(t_lst_env **new)
{
	t_lst_env	*start;
	t_lst_env	*node;
	t_lst_env	*min;

	start = *new;
	min = NULL;
	node = NULL;
	while (start->next)
	{
		min = start;
		node = start->next;
		while (node)
		{
			if (0 < ft_strncmp(min->name, node->name, \
					ft_strlen(min->name) + ft_strlen(node->name)))
					min = node;
			node = node->next;
		}
		swap(start, min);
		start = start->next;
	}
}

int	is_id_invalid(char *str)
{
	int		i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_' \
					|| str[i] == '=')
			i++;
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (1);
		}
	}
	return (0);
}

t_lst_env	*ls_exp_new(char *name, char *value)
{
	t_lst_env	*new;

	new = malloc(sizeof(t_lst_env));
	new->next = NULL;
	new->name = name;
	if (value)
		new->value =value;
	return (new);
}