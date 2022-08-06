/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pa_exp_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:14:47 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/06 09:36:54 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	len_to_quote_or_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			break ;
		if (str[i] == '\\' && (str[i + 1] != '\'' || str[i + 1] != '"'))
			i++;
		i++;
	}
	return (i);
}

static int	len_to_closing_quote(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == quote)
	{
		if (str[i] != quote)
			break ;
		if (str[i] == '\\' && (str[i + 1] != '\'' || str[i + 1] != '"'))
			i++;
		i++;
	}
	return (i);
}

static int	add_part_without_quotes(int i, char **cleaned, char *str, int i_qt)
{
	char	*helper1;
	char	*helper2;

	helper1 = ft_calloc(i_qt + 1, 1);
	ft_strlcat(helper1, &(str[i]), i_qt + 1);
	helper2 = ft_strjoin(*cleaned, helper1);
	free(*cleaned);
	free(helper1);
	*cleaned = helper2;
	i += i_qt;
	return (i);
}

static int	add_quoted_part(int i, char **cleaned, char *str, char quote)
{
	char	*helper1;
	char	*helper2;
	int		index;

	i++;
	index = len_to_closing_quote(&(str[i]), quote);
	helper1 = ft_calloc(index + 1, 1);
	ft_strlcat(helper1, &(str[i]), index + 1);
	helper2 = ft_strjoin(*cleaned, helper1);
	free(*cleaned);
	free(helper1);
	*cleaned = helper2;
	i += index;
	if (str[i])
		i++;
	return (i);
}

void	str_remove_quotes(char **str)
{
	char	*cleaned;
	int		index;
	int		i;

	cleaned = ft_strdup("");
	i = 0;
	while ((*str)[i])
	{
		index = len_to_quote_or_end(&((*str)[i]));
		if (index)
			i = add_part_without_quotes(i, &cleaned, *str, index);
		else if ((*str)[i] == '"')
			i = add_quoted_part(i, &cleaned, *str, '"');
		else if ((*str)[i] == '\'')
			i = add_quoted_part(i, &cleaned, *str, '\'');
	}
	free(*str);
	*str = cleaned;
}
