/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:58:51 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/05 18:29:29 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	inputloop(t_data *data)
{
	char	*helper1;
	char	*helper2;

	rl_catch_signals = 0;
	while (1)
	{
		data->prompt = prompt_get(data);
		data->input = readline(data->prompt);
		if (!(data->input))
			ms_quit(data, 0);
		while (not_closed(data->input))
		{
			helper1 = readline("> ");
			helper2 = ft_strjoin(data->input, helper1);
			free(data->input);
			free(helper1);
			data->input = helper2;
		}
		add_history(data->input);
		if (is_history_command(data->input))
			rl_clear_history();
		else
		{
			if (input_parse(data))
				ms_quit(data, 1);
			if (input_execute(data))
				ms_quit(data, 1);
		}
		printf("Before data_reset\n");
		data_reset(data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc > 1)
		ms_exit(1, "USAGE: <./minishell>\n");
	signalhandler_init();
	data = datastruct_init(envp);
	if (!data)
		ms_exit(1, "Error initializing data struct\n");
	inputloop(data);
	return (0);
}
