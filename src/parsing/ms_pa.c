/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:04 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/19 16:45:22 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_red_without_whitespace(char *str, t_process *proc)
{
	if (ft_strncmp(str, "<<", 2) == 0 && *(str + 2) != '<')
	{
		ls_red_addback(proc->ls_red, \
							ls_red_new("<<", str + 2));
		return (1);
	}
	else if (ft_strncmp(str, ">>", 2) == 0 && *(str + 2) != '>')
	{
		ls_red_addback(proc->ls_red, \
							ls_red_new(">>", str + 2));
		return (1);
	}
	else if (ft_strncmp(str, "<", 1) == 0 && *(str + 1) != '<')
	{
		ls_red_addback(proc->ls_red, \
							ls_red_new("<", str + 1));
		return (1);
	}
	else if (ft_strncmp(str, ">", 1) == 0 && *(str + 1) != '>')
	{
		ls_red_addback(proc->ls_red, \
							ls_red_new(">", str + 1));
		return (1);
	}
	return (0);
}

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
			if (!temp->next)
				break ;
			ls_red_addback(proc->ls_red, \
							ls_red_new(temp->str, temp->next->str));
			temp = temp->next;
			if (!temp->next)
				break ;
		}
		else if (is_red_without_whitespace(temp->str, proc))
		{
			temp = temp->next;
			continue ;
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
	ret.path = NULL;
	ret.malloc_error = 0;
	ret.fdin = STDIN_FILENO;
	ret.fdout = STDOUT_FILENO;
	ret.cmd = NULL;
	ret.ls_red = malloc(sizeof(t_lst_red **));
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
	ls_str_clear(temp);
	expand_and_sort(&ret);
	return (ret);
}

static int	parse_subprocesses(t_data *data, t_lst_str **ls_pipes)
{
	int	i;

	data->n_processes = ls_str_len(ls_pipes);
	data->processes = ft_calloc(data->n_processes + 1, sizeof(t_process));
	if (!data->processes)
		return (1);
	i = 0;
	while (i < data->n_processes)
	{
		data->processes[i] = process_init(data, ls_str_getindex(ls_pipes, i));
		data->processes[i].index = i;
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

	ls_pipes = parse_pipes(data);
	if (!ls_pipes)
		return (1);
	if (parse_subprocesses(data, ls_pipes))
	{
		ls_str_clear(ls_pipes);
		return (1);
	}
	ls_str_clear(ls_pipes);
	return (0);
}
