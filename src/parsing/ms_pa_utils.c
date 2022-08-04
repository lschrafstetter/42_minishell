/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:04 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/03 15:48:06 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static int	parse_for_pipes(t_lst_str **lst, const char *str)
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

t_lst_str	**parse_pipes(t_data *data)
{
	t_lst_str	**ret;

	(void) data;
	ret = malloc(sizeof(t_lst_str **));
	if (!ret)
		return (NULL);
	*ret = NULL;
	if (parse_for_pipes(ret, data->input))
	{
		ls_str_clear(ret);
		return (NULL);
	}
	return (ret);
}

static int	steps_to_whitespace(const char	*str)
{
	int	i;
	int	sq_open;
	int	dq_open;

	sq_open = 0;
	dq_open = 0;
	i = 0;
	while (*str \
			&& (!is_whitespace(*str) \
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

t_lst_str	**parse_for_whitespace(const char *str)
{
	t_lst_str	**ret;
	char		*temp;
	int			i;
	int			j;

	ret = malloc(sizeof(t_lst_str **));
	if (!ret)
		return (NULL);
	*ret = NULL;
	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			i++;
		j = steps_to_whitespace(&(str[i]));
		temp = malloc(j + 1);
		ft_strlcpy(temp, &(str[i]), j + 1);
		ls_str_addback(ret, (ls_str_new(temp)));
		free(temp);
		i += j;
		if (str[i] != 0)
			i++;
	}
	return (ret);
}
