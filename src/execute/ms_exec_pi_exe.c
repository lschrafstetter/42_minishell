/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pi_exe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:07:48 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/18 15:27:01 by lschrafs         ###   ########.fr       */
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
		if (process->fdin != 0)
			close(process->fdin);
		if (process->fdout != 1)
			close(process->fdout);
		return (ret);
	}
	return (-1);
}

static int	execute_nonbuiltin(t_process *process)
{
	if (ft_strchr(process->cmd[0], '/'))
	{
		if (access(process->cmd[0], F_OK))
		{
			printf("Minishell: %s: No such file or directory\n", \
													process->cmd[0]);
			return (1);
		}
		if (execve(process->cmd[0], process->cmd, \
													NULL) == -1)
			perror("Execve:");
		return (errno);
	}
	else
	{
		process->path = build_cmd_path(process);
		if (process->path)
		{
			if (execve(process->path, process->cmd, \
														NULL) == -1)
				perror("Execve:");
			return (errno);
		}
	}
	return (1);
}

void	execute_piped_process(t_process *process)
{
	int	ret;

	pipes_close(process->data, process->index);
	dup2(process->fdin, STDIN_FILENO);
	dup2(process->fdout, STDOUT_FILENO);
	if (!(*process->cmd))
		exit(0);
	if (!ft_strncmp(process->cmd[0], "exit", 5))
		exit(0);
	ret = check_builtins(process);
	if (ret != -1)
		exit(ret);
	exit(execute_nonbuiltin(process));
}
