/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:14:16 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/15 14:26:54 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void free_process(t_process process)
{
	int i;

	free_str(process.path);
	if (process.ls_red)
		ls_red_clear(process.ls_red);
	if (process.ls_cmd)
		ls_str_clear(process.ls_cmd);
	if (process.cmd)
	{
		i = 0;
		while (process.cmd[i])
		{
			free(process.cmd[i]);
			i++;
		}
		free(process.cmd);
	}
}

void data_free(t_data *data)
{
	if (!data)
		return;
	data_reset(data);
	if (data->ls_env)
		ls_env_clear(data->ls_env);
	free(data);
	data = NULL;
}

void data_reset(t_data *data)
{
	int i;

	if (data->processes)
	{
		i = 0;
		while (i < data->n_processes)
		{
			free_process(data->processes[i]);
			i++;
		}
	}
	free(data->processes);
	data->processes = NULL;
	free_str(data->input);
	free_str(data->prompt);
}
