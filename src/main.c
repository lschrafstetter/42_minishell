/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:58:51 by lschrafs          #+#    #+#             */
/*   Updated: 2022/07/30 11:31:57 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	inputloop(t_data *data)
{
	rl_catch_signals = 0;
	while (1)
	{
		data->prompt = get_prompt(data);
		data->input = readline(data->prompt);
		if (!(data->input))
			ms_quit(data);
		add_history(data->input);
		if (is_history_command(data->input))
			rl_clear_history();
		free_str(data->input);
		free_str(data->prompt);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv;
	if (argc > 1)
		ms_exit(1, "USAGE: <./minishell>\n");
	signalhandler_init();
	data = datastruct_init(envp);
	if (!data)
		ms_exit(1, "Error initializing data struct\n");
	inputloop(data);
	return (0);
}
