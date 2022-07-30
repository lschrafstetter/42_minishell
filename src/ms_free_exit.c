/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:14:16 by lschrafs          #+#    #+#             */
/*   Updated: 2022/07/30 11:29:41 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	ms_exit(int exit_code, char *message)
{
	printf("%s", message);
	exit(exit_code);
}

void	data_free(t_data *data)
{
	if (!data)
		return ;
	if (data->env)
		ls_clear(data->env);
	if (data->input)
		free_str(data->input);
	if (data->prompt)
		free_str(data->prompt);
	free(data);
	data = NULL;
}

void	ms_quit(t_data *data)
{
	int	exit_code;

	exit_code = data->exit_code;
	data_free(data);
	ms_exit(exit_code, "\n");
}
