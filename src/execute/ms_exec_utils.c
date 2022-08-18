/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:52:25 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/18 13:56:49 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_fds_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_processes)
	{
		if (data->processes[i].fdin != 0)
			close(data->processes[i].fdin);
		if (data->processes[i].fdout != 1)
			close(data->processes[i].fdout);
		i++;
	}
}

void	pipes_close(t_data *data, int index)
{
	int	i;

	i = 0;
	while (i < data->n_processes - 1)
	{
		if (!(index == i + 1))
			close(data->pipe_fd[i][0]);
		if (!(index == i))
			close(data->pipe_fd[i][1]);
		i++;
	}
}
