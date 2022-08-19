/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_piped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:06:36 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/19 15:08:04 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	pipes_init(t_data *data)
{
	int	i;

	data->pipe_fd = malloc(sizeof(int **) * (data->n_processes));
	if (!data->pipe_fd)
		return (1);
	i = 0;
	while (i < data->n_processes - 1)
	{
		data->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (pipe(data->pipe_fd[i]))
			perror("Pipe: ");
		if (data->processes[i + 1].index > 0)
			data->processes[i + 1].fdin = data->pipe_fd[i][0];
		if (i != data->processes[i].index - 1)
			data->processes[i].fdout = data->pipe_fd[i][1];
		i++;
	}
	data->pipe_fd[i] = NULL;
	return (0);
}

static int	redirects_set(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_processes)
	{
		if (set_redirections(&(data->processes[i])))
		{
			pipes_close(data, -1);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	processes_exec(t_data *data)
{
	int	*pid;
	int	i;
	int	status;

	pid = ft_calloc(sizeof(int), data->n_processes + 1);
	i = 0;
	while (i < data->n_processes)
	{
		pid[i] = fork();
		if (!pid[i])
			execute_piped_process(&(data->processes[i]));
		i++;
	}
	pipes_close(data, -1);
	process_fds_close(data, -1);
	i = 0;
	while (i < data->n_processes)
	{
		waitpid(pid[i], &status, 0);
		data->exit_code = status / 256;
		i++;
	}
	free(pid);
}

int	execute_piped_command(t_data *data)
{
	if (pipes_init(data))
		return (1);
	if (redirects_set(data))
		return (0);
	processes_exec(data);
	return (0);
}
