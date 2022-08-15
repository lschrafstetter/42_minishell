/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:58:51 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/15 14:20:48 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	inputloop(t_data *data)
{
	rl_catch_signals = 0;
	while (1)
	{
		data->prompt = prompt_get(data);
		data->input = readline(data->prompt);
		if (!(data->input))
			break ;
		while (not_closed(data->input))
		{
			printf("Quotes not closed!\n");
			free(data->input);
			data->input = readline(data->prompt);
		}
		add_history(data->input);
		if (is_history_command(data->input))
			rl_clear_history();
		else
		{
			if (input_parse(data))
				break ;
			if (input_execute(data))
				break ;
		}
		data_reset(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc > 1)
		return (print_return_error("USAGE: <./minishell>\n", 1, 1));
	signalhandler_init();
	data = datastruct_init(envp);
	if (!data)
		return (print_return_error("Error initializing data struct\n", 1, 1));
	inputloop(data);
	data_free(data);
	return (0);
}
