/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:04 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/03 15:48:11 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sort_cmd_red(t_lst_str **ls, t_process *proc)
{
	t_lst_str	*temp;

	temp = *ls;
	while (temp)
	{
		if (ft_strncmp(temp->str, "<", 2) == 0 \
			|| ft_strncmp(temp->str, "<<", 3) == 0 \
			|| ft_strncmp(temp->str, ">", 2) == 0 \
			|| ft_strncmp(temp->str, ">>", 3) == 0)
		{
			ls_env_addback(proc->ls_red, \
							ls_env_new(temp->str, temp->next->str));
			temp = temp->next;
			if (!temp->next)
				break ;
		}
		else
			ls_str_addback(proc->ls_cmd, ls_str_new(temp->str));
		temp = temp->next;
	}
}

static t_process	process_init(t_data *data, t_lst_str *str)
{
	t_process	ret;
	t_lst_str	**temp;

	ret.data = data;
	ret.path = ft_strdup(ms_getenv(data, "PATH"));
	ret.malloc_error = 0;
	ret.fdin = 0;
	ret.fdout = 1;
	ret.cmd = NULL;
	ret.ls_red = malloc(sizeof(t_lst_env **));
	ret.ls_cmd = malloc(sizeof(t_lst_str **));
	if (!ret.ls_cmd || !ret.ls_red || !str)
	{
		ret.malloc_error = 1;
		return (ret);
	}
	*(ret.ls_red) = NULL;
	*(ret.ls_cmd) = NULL;
	temp = parse_for_whitespace(str->str);
	if (!temp)
		return (ret);
	sort_cmd_red(temp, &ret);
	/////////////////////////
	t_lst_str *t;
	t = *ret.ls_cmd;
	printf("Commands:\n");
	while (t)
	{
		printf("%s\n", t->str);
		t = t->next;
	}
	printf("\n");
	//////////////////////////
	t_lst_env *te;
	te = *ret.ls_red;
	printf("Redirects:\n");
	while (te)
	{
		printf("%s und %s\n", te->name, te->value);
		te = te->next;
	}
	printf("\n");
	ls_str_clear(temp);
	expand_and_sort(&ret);
	return (ret);
}

static int	parse_subprocesses(t_data *data, t_lst_str **ls_pipes)
{
	int	i;

	data->n_processes = ls_str_len(ls_pipes);
	data->processes = malloc(sizeof(t_process) * data->n_processes + 1);
	if (!data->processes)
		return (1);
	i = 0;
	while (i < data->n_processes)
	{
		data->processes[i] = process_init(data, ls_str_getindex(ls_pipes, i));
		if (data->processes[i].malloc_error)
		{
			i = 0;
			while (i < data->n_processes)
			{
				free_process(data->processes[i]);
				i++;
			}
			free(data->processes);
			return (1);
		}
		i++;
	}
	return (0);
}

int	input_parse(t_data *data)
{
	t_lst_str	**ls_pipes;

	printf("Parsing [%s] into data!\n", data->input);
	ls_pipes = parse_pipes(data);
	if (!ls_pipes)
		return (1);
	if (parse_subprocesses(data, ls_pipes))
	{
		ls_str_clear(ls_pipes);
		return (1);
	}
	t_lst_str	*temp;
	temp = *ls_pipes;
	while (temp)
	{
		printf("%s\n", temp->str);
		temp = temp->next;
	}
	printf("Needed processes: %i\n", ls_str_len(ls_pipes));
	ls_str_clear(ls_pipes);
	return (0);
}
