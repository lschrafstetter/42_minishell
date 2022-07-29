/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 18:09:59 by lschrafs          #+#    #+#             */
/*   Updated: 2022/07/29 19:17:43 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_whitespace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
		c == '\r')
		return (1);
	return (0);
}

void	minishell_exit(int err, char *message)
{
	printf("%s", message);
	exit(err);
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

char	*get_prompt(t_data *data)
{
	char	*prompt;
	char	*helper;

	if (ft_strncmp(ms_getenv(data, "PWD"), \
					ms_getenv(data, "HOME"), \
					ft_strlen(ms_getenv(data, "HOME"))) == 0)
		helper = ft_strjoin("minishell:~", ms_getenv(data, "PWD") + \
							ft_strlen(ms_getenv(data, "HOME")));
	else
		helper = ft_strjoin("minishell:~", ms_getenv(data, "PWD"));
	prompt = ft_strjoin(helper, "$ ");
	free(helper);
	return (prompt);
}
