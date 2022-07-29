/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:58:51 by lschrafs          #+#    #+#             */
/*   Updated: 2022/07/29 11:22:38 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	//signalhandler_init();
	data = datastruct_init(envp);
	if (!data)
		exit(1);
	ft_printf("%s=%s", data->env[0]->name, data->env[0]->name);
	(void) argc;
	(void) argv;
	(void) envp;
	return (0);
}
