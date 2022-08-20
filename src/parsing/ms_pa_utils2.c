/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pa_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:04 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/20 12:01:45 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	n_bs_before_quotes(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\\' && (*str == '\'' || *str == '\''))
			i++;
		str++;
	}
	return (i);
}

void	remove_bs_before_quotes(char **str)
{
	char	*temp;
	int		i1;
	int		i2;
	int		str_new_len;

	str_new_len = ft_strlen(*str) + n_bs_before_quotes(*str);
	temp = ft_calloc(str_new_len + 1, 1);
	i1 = 0;
	i2 = 0;
	while (i1 < str_new_len)
	{
		if ((*str)[i1] == '\\' \
				&& ((*str)[i1 + 1] == '\'' || (*str)[i1 + 1] == '"'))
			i1++;
		temp[i2] = (*str)[i1];
		i1++;
		i2++;
	}
	free(*str);
	*str = temp;
}

int	num_quotes_in_env(char *str)
{
	int	i;
	int	num_quotes;

	num_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			num_quotes++;
		i++;
	}
	return (num_quotes);
}
