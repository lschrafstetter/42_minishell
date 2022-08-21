/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:08:31 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/21 21:19:54 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	set_in_red(t_process *process, t_lst_red *redirection)
{
	int	temp_fd;

	if (access(redirection->file, F_OK))
	{
		print_error(redirection->file, NULL, ": No such file or directory");
		return (1);
	}
	if (access(redirection->file, R_OK))
	{
		print_error(redirection->file, NULL, ": Permission denied");
		return (1);
	}
	if (process->fdin != 0 \
		|| (process->data->n_processes > 1 && process->fdin != 0))
		close(process->fdin);
	temp_fd = open(redirection->file, O_RDONLY);
	if (temp_fd == -1)
		return (1);
	if (process->data->n_processes > 1 && process->index > 0)
		process->data->pipe_fd[process->index - 1][0] = temp_fd;
	process->fdin = temp_fd;
	return (0);
}

static int	check_acces_out_red(t_lst_red *redirection)
{
	DIR	*temp_dir;

	if (!access(redirection->file, F_OK) && \
		access(redirection->file, W_OK))
	{
		print_error(redirection->file, NULL, ": Permission denied");
		return (1);
	}
	temp_dir = opendir(redirection->file);
	if (temp_dir)
	{
		closedir(temp_dir);
		print_error(redirection->file, NULL, ": Is a directory");
		return (1);
	}
	return (0);
}

static int	set_out_red(t_process *process, t_lst_red *redirection, int append)
{
	int	temp_fd;

	if (check_acces_out_red(redirection))
		return (1);
	if (process->fdout != 1 \
		|| (process->data->n_processes > 1 && process->fdout != 1))
		close(process->fdout);
	if (append)
		temp_fd = open(redirection->file, \
					O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		temp_fd = open(redirection->file, \
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1)
		return (1);
	if (process->data->n_processes > 1 && process->index > 0)
		process->data->pipe_fd[process->index - 1][0] = temp_fd;
	process->fdout = temp_fd;
	return (0);
}

static void	set_exit_code_failed_red(t_process *proc)
{
	proc->data->exit_code = 1;
	proc->failed_red = 1;
}

int	set_redirections(t_process *proc)
{
	t_lst_red	*temp;

	temp = *(proc->ls_red);
	while (temp)
	{
		if (temp->ambiguous_redirect)
		{
			print_error(temp->file, NULL, ": Ambiguous redirect!");
			set_exit_code_failed_red(proc);
			return (0);
		}
		else if ((!ft_strncmp(temp->red, "<", 2) && set_in_red(proc, temp)) \
			|| (!ft_strncmp(temp->red, ">", 2) && set_out_red(proc, temp, 0)) \
			|| (!ft_strncmp(temp->red, ">>", 3) && set_out_red(proc, temp, 1)))
		{
			set_exit_code_failed_red(proc);
			return (0);
		}
		else if (!ft_strncmp(temp->red, "<<", 3))
			if (set_here_doc(proc, temp))
				return (1);
		temp = temp->next;
	}
	return (0);
}
