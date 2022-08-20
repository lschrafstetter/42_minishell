/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:05:17 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/20 18:08:24 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_builtins(t_data *data)
{
	int	temp_exit_code;

	temp_exit_code = -1;
	if (!ft_strncmp(data->processes->cmd[0], "pwd", 4))
		temp_exit_code = ms_pwd(data->processes);
	else if (!ft_strncmp(data->processes->cmd[0], "echo", 5))
		temp_exit_code = ms_echo(data->processes);
	else if (!ft_strncmp(data->processes->cmd[0], "env", 4))
		temp_exit_code = ms_env(data->processes);
	else if (!ft_strncmp(data->processes->cmd[0], "cd", 3))
		temp_exit_code = ms_cd(data->processes);
	else if (!ft_strncmp(data->processes->cmd[0], "export", 7))
		temp_exit_code = ms_export(data->processes);
	else if (!ft_strncmp(data->processes->cmd[0], "unset", 6))
		temp_exit_code = ms_unset(data->processes);
	else if (!ft_strncmp(data->processes->cmd[0], "exit", 5))
		temp_exit_code = ms_exit(data->processes);
	if (temp_exit_code < 0)
		return (0);
	data->exit_code = temp_exit_code;
	return (1);
}

int	execute_single_command(t_data *data)
{
	if (data->processes[0].ls_red && set_redirections(&(data->processes[0])))
		return (0);
	if (!(data->processes[0].cmd))
		return (0);
	if (check_builtins(data))
	{
		set_underscore(data);
		return (0);
	}
	execute_single_nonbuiltin(data);
	set_underscore(data);
	return (0);
}
