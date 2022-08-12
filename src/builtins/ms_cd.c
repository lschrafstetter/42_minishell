/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 10:16:19 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/12 16:20:02 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_cd(t_process *proc)
{
	if (!proc->cmd[1])
	{
		if (*ms_getenv(proc->data, "HOME") == 0)
			return (print_return_error("minishell: cd: HOME not set\n", 1, 1));
		if (chdir(ms_getenv(proc->data, "HOME")))
		{
			printf("bash, cd: %s: No such file or directory\n", \
					ms_getenv(proc->data, "HOME"));
			return (1);
		}
		env_set_value(proc, "OLDPWD", ms_getenv(proc->data, "PWD"));
		env_set_value(proc, "PWD", ms_getenv(proc->data, "HOME"));
		return (0);
	}
	if (proc->cmd[2])
		return (print_return_error("minishell: cd: too many arguments\n", 1, 1));
	if (chdir(proc->cmd[1]))
	{
		if (errno == EACCES)
			printf("minishell: cd: %s: Permission denied\n", \
				proc->cmd[1]);
		else
			printf("minishell: cd: %s: No such file or directory\n", \
				proc->cmd[1]);
		return (1);
	}
	env_set_value(proc, "OLDPWD", ms_getenv(proc->data, "PWD"));
	env_set_value(proc, "PWD", getcwd(NULL, 0));
	return (0);
}
