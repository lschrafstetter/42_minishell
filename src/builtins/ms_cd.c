/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 10:16:19 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/07 11:07:30 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_cd(t_data *data, char **argv)
{
	if (!argv[1])
	{
		if (*ms_getenv(data, "HOME") == 0)
			return (print_return_error("minishell: cd: HOME not set\n", 1, 1));
		if (chdir(ms_getenv(data, "HOME")))
		{
			printf("bash, cd: %s: No such file or directory\n", \
					ms_getenv(data, "HOME"));
			return (1);
		}
		// export oldpwd to current
		// export current to home
		return (0);
	}
	if (argv[2])
		return (print_return_error("minishell: cd: too many arguments\n", 1, 1));
	if (chdir(ms_getenv(data, argv[1])))
	{
		printf("minishell: cd: %s: No such file or directory\n", \
				ms_getenv(data, argv[1]));
		return (1);
	}
	//oldpwd to current
	//change current to argv[1] <<<<---- special case wegen relative path
	return (0);
}
