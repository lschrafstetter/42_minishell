/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 10:16:19 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/12 15:21:04 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_cd(t_process *proc)
{
	if (!proc->cmd[1])
	{
		if (*ms_getenv(proc->data, "HOME=") == 0)
			return (print_return_error("minishell: cd: HOME not set\n", 1, 1));
		if (chdir(ms_getenv(proc->data, "HOME=")))
		{
			printf("bash, cd: %s: No such file or directory\n", \
					ms_getenv(proc->data, "HOME="));
			return (1);
		}
		//env_set_value(proc, str);
		// export oldpwd to current
		// export current to home
		return (0);
	}
	if (proc->cmd[2])
		return (print_return_error("minishell: cd: too many arguments\n", 1, 1));
	if (chdir(ms_getenv(proc->data, proc->cmd[1])))
	{
		printf("minishell: cd: %s: No such file or directory\n", \
				ms_getenv(proc->data, proc->cmd[1]));
		return (1);
	}
	//oldpwd to current
	//change current to argv[1] <<<<---- special case wegen relative path
	return (0);
}
