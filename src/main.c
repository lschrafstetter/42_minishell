/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:58:51 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/20 15:19:32 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	inputloop(t_data *data)
{
	while (1)
	{
		data->prompt = prompt_get(data);
		data->input = readline(data->prompt);
		if (!(data->input))
			break ;
		add_history(data->input);
		if (not_closed(data->input))
		{
			ft_putendl_fd("Quotes not closed!", 2);
			data_reset(data);
			continue ;
		}
		if (contains_backslash(data->input))
		{
			ft_putendl_fd("No backslash allowed!", 2);
			data_reset(data);
			continue ;
		}
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
		return (print_return_error("USAGE: <./minishell>\n", 1, 2));
	signalhandler_init();
	data = datastruct_init(envp);
	if (!data)
		return (print_return_error("Error initializing data struct\n", 1, 2));
	inputloop(data);
	data_free(data);
	write(1, "\n", 1);
	return (0);
}
