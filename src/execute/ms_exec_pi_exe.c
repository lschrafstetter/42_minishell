/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pi_exe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:07:48 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/19 19:54:42 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (ret != -1)
	{
		if (process->fdin != STDIN_FILENO)
			close(process->fdin);
		if (process->fdout != STDOUT_FILENO)
			close(process->fdout);
		pipes_close(process->data, -1);
		return (ret);
	}
	return (-1);
}

static int	execute_nonbuiltin(t_process *process)
{
	DIR	*temp_dir;

	if (ft_strchr(process->cmd[0], '/') \
		|| !ft_strncmp(process->cmd[0], ".", 2))
	{
		temp_dir = opendir(process->cmd[0]);
		if (temp_dir)
		{
			closedir(temp_dir);
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(process->cmd[0], 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (1);
		}
		if (access(process->cmd[0], F_OK))
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(process->cmd[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
		if (execve(process->cmd[0], process->cmd, \
													process->data->env) == -1)
			perror("Execve:");
		return (errno);
	}
	else
	{
		process->path = build_cmd_path(process);
		if (process->path)
		{
			if (execve(process->path, process->cmd, \
													process->data->env) == -1)
				perror("Execve:");
			return (errno);
		}
	}
	return (1);
}

void	execute_piped_process(t_process *process)
{
	int	ret;

	if (!(process->cmd) || !ft_strncmp(process->cmd[0], "exit", 5))
	{
		pipes_close(process->data, -1);
		process_fds_close(process->data, -1);
		exit(0);
	}
	pipes_close(process->data, process->index);
	process_fds_close(process->data, process->index);
	dup2(process->fdin, STDIN_FILENO);
	dup2(process->fdout, STDOUT_FILENO);
	ret = check_builtins(process);
	if (ret != -1)
		exit(ret);
	exit(execute_nonbuiltin(process));
}
