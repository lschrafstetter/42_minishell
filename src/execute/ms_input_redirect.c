/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:08:31 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/15 18:32:08 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	set_in_red(t_process *process, t_lst_red *redirection)
{
	if (access(redirection->filename, F_OK))
	{
		printf("Minishell: %s: No such file or directory\n", \
														redirection->filename);
		return (1);
	}
	if (access(redirection->filename, R_OK))
	{
		printf("Minishell: %s: Permission denied\n", redirection->filename);
		return (1);
	}
	process->fdin = open(redirection->filename, O_RDONLY);
	if (process->fdin == -1)
		return (1);
	return (0);
}

static int	set_out_red(t_process *process, t_lst_red *redirection, int append)
{
	if (!access(redirection->filename, F_OK && \
		access(redirection->filename, W_OK)))
	{
		printf("Minishell: %s: Permission denied\n", redirection->filename);
		return (1);
	}
	if (append)
		process->fdout = open(redirection->filename, \
					O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		process->fdout = open(redirection->filename, \
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (process->fdout == -1)
		return (1);
	return (0);
}

static int	set_here_doc(t_process *process, t_lst_red *redirection)
{
	(void) process;
	(void) redirection;
	return (0);
}

int	set_redirections(t_process *proc)
{
	t_lst_red	*temp;

	temp = *(proc->ls_red);
	while (temp)
	{
		if (temp->ambiguous_redirect)
			return (print_return_error("Ambiguous redirect!", 1, 1));
		if (!ft_strncmp(temp->redirection, "<", 2) && \
												set_in_red(proc, temp))
			return (1);
		if (!ft_strncmp(temp->redirection, ">", 2) && \
												set_out_red(proc, temp, 0))
			return (1);
		if (!ft_strncmp(temp->redirection, ">>", 3) && \
												set_out_red(proc, temp, 1))
			return (1);
		if (!ft_strncmp(temp->redirection, "<<", 3) && \
												set_here_doc(proc, temp))
			return (1);
		temp = temp->next;
	}
	return (0);
}
