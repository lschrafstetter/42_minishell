/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:04 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/01 14:36:36 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_lst_str	**parse_pipes(t_data *data)
{
	t_lst_str	**ret;

	(void) data;
	ret = malloc(sizeof(t_lst_str **));
	if (!ret)
		return (NULL);
	*ret = NULL;
	return (ret);
}

int	input_parse(t_data *data)
{
	t_lst_str	**ls_pipes;

	printf("Parsing [%s] into data!\n", data->input);
	ls_pipes = parse_pipes(data);
	if (!ls_pipes)
		return (1);
	ls_str_clear(ls_pipes);
	return (0);
}
