/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:16 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/11 13:00:45 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	input_execute(t_data *data)
{
	(void) data;
	printf("Executing command [%s]!\n", data->input);
	if (!ft_strncmp(data->processes->cmd[0], "pwd", 4))
		ms_pwd(data->processes);
	else if (!ft_strncmp(data->processes->cmd[0], "echo", 5))
		ms_echo(data->processes);
	else if (!ft_strncmp(data->processes->cmd[0], "env", 4))
		ms_env(data->processes);
	else if (!ft_strncmp(data->processes->cmd[0], "cd", 3))
		ms_cd(data->processes);
	else if (!ft_strncmp(data->processes->cmd[0], "export", 7))
		ms_export(data->processes);
	else if (!ft_strncmp(data->processes->cmd[0], "unset", 6))
		ms_unset(data->processes);
	return (0);
}
