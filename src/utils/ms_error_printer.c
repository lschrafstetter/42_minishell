/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_printer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:31:11 by dfranke           #+#    #+#             */
/*   Updated: 2022/08/20 15:43:54 by lschrafs         ###   ########.fr       */
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
