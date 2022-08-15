/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:16 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/15 14:17:36 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	execute_single_command(t_data *data)
{
	printf("Executing single command [%s]!\n", data->input);
	if (!ft_strncmp(data->processes->cmd[0], "exit", 5))
		return (1);
	else if (!ft_strncmp(data->processes->cmd[0], "pwd", 4))
		return (ms_pwd(data->processes));
	else if (!ft_strncmp(data->processes->cmd[0], "echo", 5))
		return (ms_echo(data->processes));
	else if (!ft_strncmp(data->processes->cmd[0], "env", 4))
		return (ms_env(data->processes));
	else if (!ft_strncmp(data->processes->cmd[0], "cd", 3))
		return (ms_cd(data->processes));
	else if (!ft_strncmp(data->processes->cmd[0], "export", 7))
		return (ms_export(data->processes));
	else if (!ft_strncmp(data->processes->cmd[0], "unset", 6))
		return (ms_unset(data->processes));
	return (0);
}

static int	execute_piped_command(t_data *data)
{
	printf("Executing piped command [%s]!\n", data->input);
	return (0);
}

int	input_execute(t_data *data)
{
	if (data->n_processes == 0)
		return (0);
	if (data->n_processes == 1)
		return (execute_single_command(data));
	return (execute_piped_command(data));
}
