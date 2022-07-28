/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfranke <dfranke@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:59:17 by lschrafs          #+#    #+#             */
/*   Updated: 2022/07/28 14:06:55 by dfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_lst_env
{
	char				*name;
	char				*value;
	struct s_lst_str	*next;
}	t_lst_env;

typedef struct s_lst_processes
{
	int					fdin;
	int					fdout;
	char				**cmd;
	char				*path;
}	t_lst_processes;

typedef struct s_data
{
	int				exit_code;
	t_lst_env		**env;
	t_lst_processes	*processes;
	int				n_processes;
}	t_data;


void	signalhandler_init(void);

#endif