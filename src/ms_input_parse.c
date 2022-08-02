/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:04 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/02 10:24:38 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	steps_to_pipe(const char	*str)
{
	int	i;
	int	sq_open;
	int	dq_open;

	sq_open = 0;
	dq_open = 0;
	i = 0;
	while (*str \
			&& (*str != '|' \
			|| *(str + 1) == '|' \
			|| (i > 0 && *str == '|' && *(str - 1) == '|') \
			|| sq_open || dq_open))
	{
		if (*str == '\'' && !dq_open)
			sq_open = 1 - sq_open;
		if (*str == '"' && !sq_open)
			dq_open = 1 - dq_open;
		i++;
		str++;
	}
	return (i);
}

static int	add_pipes(t_lst_str **lst, const char *str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (str[i])
	{
		j = steps_to_pipe(&(str[i]));
		temp = malloc(j + 1);
		ft_strlcpy(temp, &(str[i]), j + 1);
		ls_str_addback(lst, (ls_str_new(temp)));
		free(temp);
		i += j;
		if (str[i] != 0)
			i++;
	}
	return (0);
}

static t_lst_str	**parse_pipes(t_data *data)
{
	t_lst_str	**ret;

	(void) data;
	ret = malloc(sizeof(t_lst_str **));
	if (!ret)
		return (NULL);
	*ret = NULL;
	if (add_pipes(ret, data->input))
	{
		ls_str_clear(ret);
		return (NULL);
	}
	return (ret);
}

int	input_parse(t_data *data)
{
	t_lst_str	**ls_pipes;

	printf("Parsing [%s] into data!\n", data->input);
	ls_pipes = parse_pipes(data);
	if (!ls_pipes)
		return (1);
	t_lst_str	*temp;
	temp = *ls_pipes;
	while (temp)
	{
		printf("%s\n", temp->str);
		temp = temp->next;
	}
	printf("Needed processes: %i\n", ls_str_len(ls_pipes));
	ls_str_clear(ls_pipes);
	return (0);
}
