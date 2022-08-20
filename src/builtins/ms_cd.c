/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 10:16:19 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/20 15:44:25 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	cd_no_params(t_process *proc)
{
	if (*ms_getenv(proc->data, "HOME") == 0)
		return (print_return_error("minishell: cd: \
				HOME not set\n", 1, STDERR_FILENO));
	if (chdir(ms_getenv(proc->data, "HOME")))
	{
		print_error(ms_getenv(proc->data, "HOME"), "cd", \
					": No such file or directory");
		return (1);
	}
	env_set_value(proc->data, "OLDPWD", ms_getenv(proc->data, "PWD"));
	env_set_value(proc->data, "PWD", ms_getenv(proc->data, "HOME"));
	return (0);
}

int	ms_cd(t_process *proc)
{
	char	*cwd;

	if (!proc->cmd[1])
		return (cd_no_params(proc));
	if (proc->cmd[2])
		return (print_return_error("minishell: cd: \
				too many arguments\n", 1, STDERR_FILENO));
	if (chdir(proc->cmd[1]))
	{
		if (errno == EACCES)
			print_error(proc->cmd[1], "cd", ": Permission denied");
		else
			print_error(proc->cmd[1], "cd", ": No such file or directory");
		return (1);
	}
	env_set_value(proc->data, "OLDPWD", ms_getenv(proc->data, "PWD"));
	cwd = getcwd(NULL, 0);
	env_set_value(proc->data, "PWD", cwd);
	free_str(&cwd);
	return (0);
}
