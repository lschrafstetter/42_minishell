/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_si_exe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:05:17 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/20 23:10:03 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*check_path(t_process *process)
{
	int		i;
	char	**paths;
	char	*helper;

	paths = ft_split(ms_getenv(process->data, "PATH"), ':');
	helper = NULL;
	i = 0;
	while (paths[i])
	{
		helper = ft_strthreejoin(paths[i], "/", process->cmd[0]);
		if (!access(helper, F_OK))
			break ;
		free_str(&helper);
		i++;
	}
	free_strarray(paths);
	return (helper);
}

char	*build_cmd_path(t_process *process)
{
	char	*helper;

	helper = check_path(process);
	if (!helper)
	{
		print_error(process->cmd[0], NULL, ": command not found");
		process->data->exit_code = 127;
		return (NULL);
	}
	if (access(helper, X_OK))
	{
		print_error(helper, NULL, ": Permission denied");
		free_str(&helper);
		process->data->exit_code = 126;
		return (NULL);
	}
	return (helper);
}

static void	execute_path(t_data *data, int *pid, int *status)
{
	DIR	*temp_dir;

	temp_dir = opendir(data->processes->cmd[0]);
	if (temp_dir)
	{
		closedir(temp_dir);
		print_error(data->processes->cmd[0], NULL, ": is a directory");
		data->exit_code = 126;
		return ;
	}
	if (access(data->processes->cmd[0], F_OK))
	{
		print_error(data->processes->cmd[0], NULL, \
					": No such file or directory");
		data->exit_code = 127;
		return ;
	}
	if (access(data->processes->cmd[0], X_OK))
	{
		print_error(data->processes->cmd[0], NULL, ": Permission denied");
		data->exit_code = 126;
		return ;
	}
	*pid = fork();
	if (!(*pid))
	{
		dup2(data->processes->fdin, STDIN_FILENO);
		dup2(data->processes->fdout, STDOUT_FILENO);
		execve(data->processes->cmd[0], data->processes->cmd, data->env);
		exit(errno);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(*pid, status, 0);
	if (WIFSIGNALED(*status))
		data->exit_code = 130;
	else
		data->exit_code = *status / 256;
	signalhandler_init();
}

void	execute_single_nonbuiltin(t_data *data)
{
	int	pid;
	int	status;

	if (ft_strchr(data->processes->cmd[0], '/') \
		|| !ft_strncmp(data->processes->cmd[0], ".", 2))
	{
		execute_path(data, &pid, &status);
	}
	else
	{
		data->processes[0].path = build_cmd_path(&(data->processes[0]));
		if (data->processes[0].path)
		{
			pid = fork();
			if (!pid)
			{
				dup2(data->processes->fdin, STDIN_FILENO);
				dup2(data->processes->fdout, STDOUT_FILENO);
				execve(data->processes->path, data->processes->cmd, data->env);
				exit(errno);
			}
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &status, 0);
			if (WIFSIGNALED(status))
				data->exit_code = 130;
			else
				data->exit_code = status / 256;
			signalhandler_init();
		}
	}
}
