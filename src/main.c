/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:58:51 by lschrafs          #+#    #+#             */
/*   Updated: 2022/07/29 19:10:14 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	inputloop(t_data *data)
{
	while (1)
	{
		data->prompt = get_prompt(data);
		data->input = readline(data->prompt);
		if (!(data->input))
		{
			write(1, "\n", 1);
			exit(0);
		}
		add_history(data->input);
		if (is_history_command(data->input))
			rl_clear_history();
		free(data->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv;
	if (argc > 1)
		minishell_exit(1, "USAGE: <./minishell>\n");
	//signalhandler_init();
	data = datastruct_init(envp);
	if (!data)
		minishell_exit(1, "Error initializing data struct\n");
	inputloop(data);
	return (0);
}
