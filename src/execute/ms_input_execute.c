/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:16 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/17 15:20:12 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_builtins(t_data *data)
{
	if (!ft_strncmp(data->processes->cmd[0], "pwd", 4))
	{
		data->exit_code = ms_pwd(data->processes);
		return (1);
	}
	else if (!ft_strncmp(data->processes->cmd[0], "echo", 5))
	{
		data->exit_code = ms_echo(data->processes);
		return (1);
	}
	else if (!ft_strncmp(data->processes->cmd[0], "env", 4))
	{
		data->exit_code = ms_env(data->processes);
		return (1);
	}
	else if (!ft_strncmp(data->processes->cmd[0], "cd", 3))
	{
		data->exit_code = ms_cd(data->processes);
		return (1);
	}
	else if (!ft_strncmp(data->processes->cmd[0], "export", 7))
	{
		data->exit_code = ms_export(data->processes);
		return (1);
	}
	else if (!ft_strncmp(data->processes->cmd[0], "unset", 6))
	{
		data->exit_code = ms_unset(data->processes);
		return (1);
	}
	return (0);
}

char	*build_cmd_path(t_data *data)
{
	int		i;
	char	**paths;
	char	*helper;

	paths = ft_split(ms_getenv(data, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		helper = ft_strthreejoin(paths[i], "/", data->processes[0].cmd[0]);
		if (!access(helper, F_OK))
			break ;
		free_str(helper);
		i++;
	}
	if (!helper)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(data->processes[0].cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		return (NULL);
	}
	if (access(helper, F_OK))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(helper, 2);
		ft_putendl_fd(": Permission denied", 2);
		free_str(helper);
		return (NULL);
	}
	return (helper);
}

static void	execute_nonbuiltin(t_data *data)
{
	int	pid;
	int	status;

	if (ft_strchr(data->processes->cmd[0], '/'))
	{
		if (access(data->processes->cmd[0], F_OK))
		{
			printf("Minishell: %s: No such file or directory\n", \
													data->processes->cmd[0]);
			return ;
		}
		pid = fork();
		if (!pid)
		{
			dup2(data->processes->fdin, STDIN_FILENO);
			dup2(data->processes->fdout, STDOUT_FILENO);
			if (execve(data->processes->cmd[0], data->processes->cmd, \
														NULL) == -1)
				perror("Execve:");
			exit(0);
		}
		waitpid(pid, &status, 0);
	}
	else
	{
		data->processes[0].path = build_cmd_path(data);
		if (data->processes[0].path)
		{
			pid = fork();
			if (!pid)
			{
				dup2(data->processes->fdin, STDIN_FILENO);
				dup2(data->processes->fdout, STDOUT_FILENO);
				if (execve(data->processes->path, data->processes->cmd, \
															NULL) == -1)
					perror("Execve:");
				exit(0);
			}
			waitpid(pid, &status, 0);
		}
	}
}

static int	execute_single_command(t_data *data)
{
	printf("Executing single command [%s]!\n", data->input);
	if (data->processes[0].ls_red && set_redirections(&(data->processes[0])))
		return (0);
	if (!(data->processes[0].cmd))
		return (0);
	if (!ft_strncmp(data->processes[0].cmd[0], "exit", 5))
		return (1);
	if (check_builtins(data))
		return (0);
	execute_nonbuiltin(data);
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
