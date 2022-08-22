/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:12:35 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/22 11:54:33 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_name(char *env_line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (env_line[i])
	{
		if (env_line[i] == '\0' || env_line[i] == '=')
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

static void	add_env(char **envp, t_data *data)
{
	char	*tmp_name;
	char	*tmp_value;
	int		sh_lvl;
	int		err;

	tmp_name = get_env_name(*envp);
	if (!ft_strncmp(tmp_name, "SHLVL", 6))
	{
		err = 0;
		sh_lvl = ft_atoi_e(getenv(tmp_name), &err);
		if (sh_lvl < 0 || err == 1)
			sh_lvl = 0;
		tmp_value = ft_itoa(sh_lvl + 1);
		if (tmp_value)
		{
			ls_env_addback(data->ls_env, (ls_env_new(tmp_name, tmp_value)));
			free (tmp_value);
		}
	}
	else
		ls_env_addback(data->ls_env, (ls_env_new(tmp_name, getenv(tmp_name))));
	if (tmp_name)
		free(tmp_name);
}

int	env_init(char **envp, t_data *data)
{
	data->ls_env = malloc(sizeof(t_lst_env **));
	if (!(data->ls_env))
		return (1);
	*(data->ls_env) = NULL;
	while (*envp)
	{
		add_env(envp, data);
		envp++;
	}
	env_set_value(data, "OLDPWD", NULL);
	if (!(data->env))
		data->env = lst_env_to_strarray(data->ls_env);
	return (0);
}

t_data	*datastruct_init(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->n_processes = 0;
	data->exit_code = 0;
	data->input = NULL;
	data->prompt = NULL;
	data->processes = NULL;
	data->env = NULL;
	data->pipe_fd = NULL;
	if (env_init(envp, data))
	{
		data_free(data);
		return (NULL);
	}
	return (data);
}
