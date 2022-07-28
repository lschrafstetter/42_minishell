/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:58:51 by lschrafs          #+#    #+#             */
/*   Updated: 2022/07/28 14:27:26 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_env_name(char *env_line)
{
	int		i;
	int		j;
	char	*str;
	
	i = 0;
	while (env_line)
	{
		if (env_line == '=')
			break ;
		i++;
	}
	str = malloc(i + 1);
	j = 0;
	while (j < (i + 1))
	{
		str[j] = env_line[j];
		j++;
	}
	return (str);
}

int	env_init(char **envp, t_data *data)
{
	char	*tmp_name;
	
	data->env = malloc(sizeof(t_lst_env **));
	if (!(data->env))
		return (1);
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

int	datastruct_init(char **envp, t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	env_init(envp, data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	
	signalhandler_init();
	if (datastruct_init(envp, data))
		exit(1);
	(void) argc;
	(void) argv;
	(void) envp;
	return (0);
}