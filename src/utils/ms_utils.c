/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:09:59 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/20 10:31:12 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_whitespace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
		c == '\r')
		return (1);
	return (0);
}

int	is_history_command(char *str)
{
	while (is_whitespace(*str))
		str++;
	if (ft_strncmp(str, "history", 7) != 0)
		return (0);
	str += 7;
	if (!is_whitespace(*str))
		return (0);
	while (is_whitespace(*str))
		str++;
	if (ft_strncmp(str, "-c", 2) != 0)
		return (0);
	str += 2;
	if (!is_whitespace(*str) && *str != '\0')
		return (0);
	return (1);
}

char	*prompt_get(t_data *data)
{
	char	*prompt;
	char	*helper;

	if (ft_strncmp(ms_getenv(data, "PWD"), \
					ms_getenv(data, "HOME"), \
					ft_strlen(ms_getenv(data, "HOME"))) == 0)
		helper = ft_strjoin("minishell:~", ms_getenv(data, "PWD") + \
							ft_strlen(ms_getenv(data, "HOME")));
	else
		helper = ft_strjoin("minishell:", ms_getenv(data, "PWD"));
	prompt = ft_strjoin(helper, "$ ");
	free(helper);
	return (prompt);
}

int	not_closed(const char *str)
{
	int	sq_open;
	int	dq_open;

	sq_open = 0;
	dq_open = 0;
	while (*str)
	{
		if (*str == '\'' && !dq_open)
			sq_open = 1 - sq_open;
		if (*str == '"' && !sq_open)
			dq_open = 1 - dq_open;
		str++;
	}
	return (sq_open || dq_open);
}

int	print_return_error(char *str, int err_num, int fd)
{
	write(fd, str, ft_strlen(str));
	return (err_num);
}

int	contains_backslash(const char *str)
{
	while (*str)
	{
		if (*str == '\\')
			return (1);
		str++;
	}
	return (0);
}
