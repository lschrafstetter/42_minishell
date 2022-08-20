/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_printer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:31:11 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/20 15:32:39 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error(char *argument, char *cmd, char *message)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	if (!cmd)
	{
		ft_putstr_fd(argument, STDERR_FILENO);
		ft_putendl_fd(message, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(argument, STDERR_FILENO);
		ft_putendl_fd(message, STDERR_FILENO);
	}
}