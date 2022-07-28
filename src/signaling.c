/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:21:47 by lschrafs          #+#    #+#             */
/*   Updated: 2022/07/28 13:22:35 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void    handler(int signum)
{
	if (signum == SIGINT)
	{
    	write(1, "\n", 1);
    	rl_replace_line("", 1);
    	rl_on_new_line();
    	rl_redisplay();
	}
}

void	signalhandler_init(void)
{
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
}