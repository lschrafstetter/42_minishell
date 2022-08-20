/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:58:51 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/20 22:09:42 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_input(t_data *data)
{
	data->prompt = prompt_get(data);
	data->input = readline(data->prompt);
	if (!(data->input))
		return (1);
	add_history(data->input);
	if (not_closed(data->input))
	{
		ft_putendl_fd("Quotes not closed!", STDERR_FILENO);
		data_reset(data);
		return (2);
	}
	if (contains_backslash(data->input))
	{
		ft_putendl_fd("No backslash allowed!", STDERR_FILENO);
		data_reset(data);
		return (2);
	}
	return (0);
}

static void	inputloop(t_data *data)
{
	int	input_error;

	while (1)
	{
		input_error = get_input(data);
		if (input_error == 1)
			break ;
		if (input_error == 2)
			continue ;
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
