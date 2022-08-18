/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:16 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/18 10:35:09 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	input_execute(t_data *data)
{
	if (data->n_processes == 0)
		return (0);
	if (data->n_processes == 1)
		return (execute_single_command(data));
	return (execute_piped_command(data));
}
