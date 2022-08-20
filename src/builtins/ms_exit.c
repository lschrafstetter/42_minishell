/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:03:02 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/20 18:52:45 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	string_isonlynum(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ms_exit(t_process *process)
{
	int	save_exit_code;

	if (!(process->cmd[1]))
	{
		data_free(process->data);
		exit(0);
	}
	if (!string_isonlynum(process->cmd[1]))
	{
		print_error(process->cmd[1], "exit", ": numeric argument required");
		data_free(process->data);
		exit(2);
	}
	if (process->cmd[2])
	{
		print_error("exit: ", NULL, "too many aguments");
		return (1);
	}
	save_exit_code = ft_atoi(process->cmd[1]);
	data_free(process->data);
	exit(save_exit_code % 255);
}
