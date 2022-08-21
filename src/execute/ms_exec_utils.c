/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:52:25 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/21 21:13:15 by lschrafs         ###   ########.fr       */
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
		if (!*(data->processes[0].cmd + i + 1))
			env_set_value(data, "_", data->processes[0].cmd[i]);
		i++;
	}
}

//Only for a path execution of a single process command
int	check_acces_set_exitcode(t_data *data)
{
	DIR	*temp_dir;

	temp_dir = opendir(data->processes->cmd[0]);
	if (temp_dir)
	{
		closedir(temp_dir);
		print_error(data->processes->cmd[0], NULL, ": is a directory");
		data->exit_code = 126;
		return (1);
	}
	if (access(data->processes->cmd[0], F_OK))
	{
		print_error(data->processes->cmd[0], NULL, \
					": No such file or directory");
		data->exit_code = 127;
		return (1);
	}
	if (access(data->processes->cmd[0], X_OK))
	{
		print_error(data->processes->cmd[0], NULL, ": Permission denied");
		data->exit_code = 126;
		return (1);
	}
	return (0);
}
