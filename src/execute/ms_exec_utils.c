/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:52:25 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/19 16:43:19 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_fds_close(t_data *data, int index_exclude)
{
	int	i;

	i = 0;
	while (i < data->n_processes)
	{
		if (i != index_exclude && data->processes[i].fdin != 0)
			close(data->processes[i].fdin);
		if (i != index_exclude && data->processes[i].fdout != 1)
			close(data->processes[i].fdout);
		i++;
	}
}

void	pipes_close(t_data *data, int index_exclude)
{
	int	i;

	i = 0;
	while (i < data->n_processes - 1)
	{
		if (!(index_exclude == i + 1))
			close(data->pipe_fd[i][0]);
		if (!(index_exclude == i))
			close(data->pipe_fd[i][1]);
		i++;
	}
}

void	set_underscore(t_data *data)
{
	int	i;

	i = 0;
	while (data->processes[0].cmd[i])
	{
		if (!*(data->processes[0].cmd + i + 2))
			env_set_value(data, "_", data->processes[0].cmd[i + 1]);
		i++;
	}
}
