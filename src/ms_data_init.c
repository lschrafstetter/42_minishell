/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:12:35 by lschrafs          #+#    #+#             */
/*   Updated: 2022/07/29 18:08:13 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_name(char *env_line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (env_line[i])
	{
		if (env_line[i] == '=')
			break ;
		i++;
	}
	str = malloc(i + 1);
	j = 0;
	while (j < i)
	{
		str[j] = env_line[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	env_init(char **envp, t_data *data)
{
	char	*tmp_name;

	data->env = malloc(sizeof(t_lst_env **));
	if (!(data->env))
		return (1);
	*(data->env) = NULL;
	while (*envp)
	{
		tmp_name = get_env_name(*envp);
		ls_addback(data->env, (ls_new(tmp_name, getenv(tmp_name))));
		if (tmp_name)
			free(tmp_name);
		envp++;
	}
	return (0);
}

t_data	*datastruct_init(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	env_init(envp, data);
	data->n_processes = 0;
	data->exit_code = 0;
	return (data);
}
