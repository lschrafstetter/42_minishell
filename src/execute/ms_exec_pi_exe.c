/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pi_exe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:07:48 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/22 11:57:13 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_all_std_fds(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

static int	check_builtins(t_process *process)
{
	int	ret;

	ret = -1;
	if (!ft_strncmp(process->cmd[0], "pwd", 4))
		ret = ms_pwd(process);
	else if (!ft_strncmp(process->cmd[0], "echo", 5))
		ret = ms_echo(process);
	else if (!ft_strncmp(process->cmd[0], "env", 4))
		ret = ms_env(process);
	else if (!ft_strncmp(process->cmd[0], "cd", 3))
		ret = ms_cd(process);
	else if (!ft_strncmp(process->cmd[0], "export", 7))
		ret = ms_export(process);
	else if (!ft_strncmp(process->cmd[0], "unset", 6))
		ret = ms_unset(process);
	else if (!ft_strncmp(process->cmd[0], "exit", 5))
		ret = ms_exit(process);
	if (ret != -1)
	{
		process_fds_close(process->data, -1);
		pipes_close(process->data, -1);
		close_all_std_fds();
		return (ret);
	}
	return (-1);
}

static	int	execute_path(t_process *process)
{
	DIR	*temp_dir;

	temp_dir = opendir(process->cmd[0]);
	if (temp_dir)
	{
		closedir(temp_dir);
		print_error(process->cmd[0], NULL, ": Is a directory");
		return (126);
	}
	if (access(process->cmd[0], F_OK))
	{
		print_error(process->cmd[0], NULL, ": No such file or directory");
		return (127);
	}
	if (access(process->cmd[0], X_OK))
	{
		print_error(process->cmd[0], NULL, ": Permission denied");
		return (126);
	}
	if (execve(process->cmd[0], process->cmd, \
												process->data->env) == -1)
		perror("Execve:");
	return (errno);
}

static int	execute_nonbuiltin(t_process *process)
{
	int	temp_exit_code;

	if (ft_strchr(process->cmd[0], '/') \
		|| !ft_strncmp(process->cmd[0], ".", 2))
	{
		temp_exit_code = execute_path(process);
		pipes_close(process->data, -1);
		process_fds_close(process->data, -1);
		return (temp_exit_code);
	}
	else
	{
		process->path = build_cmd_path(process);
		if (process->path)
		{
			execve(process->path, process->cmd, process->data->env);
			return (errno);
		}
		pipes_close(process->data, -1);
		process_fds_close(process->data, -1);
	}
	return (1);
}

void	execute_piped_process(t_process *process)
{
	int	ret;

	pipes_close(process->data, process->index);
	process_fds_close(process->data, process->index);
	dup2(process->fdin, STDIN_FILENO);
	dup2(process->fdout, STDOUT_FILENO);
	ret = check_builtins(process);
	if (ret != -1)
		exit(ret);
	exit(execute_nonbuiltin(process));
}
