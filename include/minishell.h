/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:59:17 by lschrafs          #+#    #+#             */
/*   Updated: 2022/07/29 11:20:52 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
	struct s_lst_env	*next;
	char				*name;
	char				*value;
}	t_lst_env;

typedef struct s_lst_processes
{
	int					fdin;
	int					fdout;
	char				**cmd;
	char				*path;
	struct s_data		*data;
}	t_lst_processes;

typedef struct s_data
{
	int				exit_code;
	t_lst_env		**env;
	t_lst_processes	*processes;
	int				n_processes;
}	t_data;

void		signalhandler_init(void);
t_data		*datastruct_init(char **envp);

t_lst_env	*ls_new(char *name, char *value);
void		ls_addfront(t_lst_env **lst, t_lst_env *new);
void		ls_addback(t_lst_env **lst, t_lst_env *new);
void		ls_clear(t_lst_env **lst);

#endif