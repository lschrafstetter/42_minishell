/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 10:16:19 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/17 15:40:51 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	cd_no_params(t_process *proc)
{
	if (*ms_getenv(proc->data, "HOME") == 0)
		return (print_return_error("minishell: cd: HOME not set\n", 1, 1));
	if (chdir(ms_getenv(proc->data, "HOME")))
	{
		printf("bash, cd: %s: No such file or directory\n", \
				ms_getenv(proc->data, "HOME"));
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
	env_set_value(proc->data, "OLDPWD", ms_getenv(proc->data, "PWD"));
	cwd = getcwd(NULL, 0);
	env_set_value(proc->data, "PWD", cwd);
	free_str(&cwd);
	return (0);
}
