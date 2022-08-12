/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:23:26 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/11 17:26:17 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*add_eq(char *str)
{
	int		i;
	char	*str_eq;

	i = 0;
	str_eq = malloc(ft_strlen(str) + 2);
	while (str[i])
	{
		str_eq[i] = str[i];
		i++;
	}
	str_eq[i++] = '=';
	str_eq[i] = '\0';
	return (str_eq);
}
