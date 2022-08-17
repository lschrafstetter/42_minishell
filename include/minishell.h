/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 16:59:17 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/17 09:37:34 by lschrafs         ###   ########.fr       */
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
# include <sys/types.h>
# include <dirent.h>
# include <sys/wait.h>

/* LIST STRUCTS */

typedef struct s_lst_str
{
	struct s_lst_str	*next;
	char				*str;
}	t_lst_str;

typedef struct s_lst_env
{
	struct s_lst_env	*next;
	char				*name;
	char				*value;
}	t_lst_env;

typedef struct s_lst_red
{
	struct s_lst_red	*next;
	char				*red;
	char				*file;
	int					ambiguous_redirect;
}	t_lst_red;

/* SUBPROCESS STRUCT */

typedef struct s_process
{
	int					malloc_error;
	int					fdin;
	int					fdout;
	char				**cmd;
	t_lst_red			**ls_red;
	t_lst_str			**ls_cmd;
	char				*path;
	struct s_data		*data;
}	t_process;

/* GENERAL DATA STRUCT */

typedef struct s_data
{
	t_lst_env			**ls_env;
	t_process			*processes;
	char				**env;
	char				*input;
	char				*prompt;
	int					n_processes;
	int					exit_code;
}	t_data;

/* INITIALIZATION */

void		signalhandler_init(void);
t_data		*datastruct_init(char **envp);

/* LISTS */

t_lst_str	*ls_str_new(char *str);
void		ls_str_addfront(t_lst_str **lst, t_lst_str *new);
void		ls_str_addback(t_lst_str **lst, t_lst_str *new);
void		ls_str_clear(t_lst_str **lst);
int			ls_str_len(t_lst_str **lst);
t_lst_str	*ls_str_getindex(t_lst_str **lst, int index);
char		**lst_str_to_strarray(t_lst_str **lst);

t_lst_env	*ls_env_new(char *name, char *value);
void		ls_env_addfront(t_lst_env **lst, t_lst_env *new);
void		ls_env_addback(t_lst_env **lst, t_lst_env *new);
void		ls_env_clear(t_lst_env **lst);
t_lst_env	**copy_env_lst(t_lst_env **env);
t_lst_env	*ls_env_contains_name(t_lst_env **lst, char *str);
int			ls_env_len(t_lst_env **lst);
char		**lst_env_to_strarray(t_lst_env **lst);

t_lst_red	*ls_red_new(char *redirection, char *filename);
void		ls_red_addfront(t_lst_red **lst, t_lst_red *new);
void		ls_red_addback(t_lst_red **lst, t_lst_red *new);
void		ls_red_clear(t_lst_red **lst);

/* ENV */

char		*get_env_name(char *env_line);
char		*ms_getenv(t_data *data, char *name);

/* PARSING */

int			input_parse(t_data *data);
t_lst_str	**parse_pipes(t_data *data);
t_lst_str	**parse_for_whitespace(const char *str);

/* EXPAND */
void		expand_and_sort(t_process *ret);
void		str_expand(char **str, t_process *process);
void		str_remove_quotes(char **str);
void		expand_list_by_whitespace(t_lst_str **node);
void		remove_backslashes_before_quotes(char **str);

/* EXECUTING */

int			input_execute(t_data *data);
int			set_redirections(t_process *proc);

/* BUILTINS */

int			ms_cd(t_process *proc);
int			ms_env(t_process *proc);
int			ms_export(t_process *proc);
int			ms_pwd(t_process *proc);
int			ms_echo(t_process *proc);
int			ms_unset(t_process *proc);

/* UTILS */

void		ms_quit(t_data *data, int err);
void		ms_exit(int err, char *message);
void		data_free(t_data *data);
void		free_str(char *str);
void		free_process(t_process	process);
void		data_reset(t_data *data);
int			is_whitespace(int c);
int			is_history_command(char *str);
char		*prompt_get(t_data *data);
int			not_closed(const char *str);
int			print_return_error(char *str, int err_num, int fd);
int			env_set_value(t_data *data, char *name, char *value);
int			num_quotes_in_env(char *str);

int			is_id_invalid(char *str);
void		sort_new_lst(t_lst_env **new);
t_lst_env	*ls_exp_new(char *name, char *value);

#endif