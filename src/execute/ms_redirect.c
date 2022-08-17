/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:08:31 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/17 09:18:06 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	set_in_red(t_process *process, t_lst_red *redirection)
{
	if (access(redirection->file, F_OK))
	{
		printf("Minishell: %s: No such file or directory\n", \
														redirection->file);
		return (1);
	}
	if (access(redirection->file, R_OK))
	{
		printf("Minishell: %s: Permission denied\n", redirection->file);
		return (1);
	}
	process->fdin = open(redirection->file, O_RDONLY);
	if (process->fdin == -1)
		return (1);
	printf("%i\n", process->fdin);
	return (0);
}

static int	set_out_red(t_process *process, t_lst_red *redirection, int append)
{
	if (!access(redirection->file, F_OK) && \
		access(redirection->file, W_OK))
	{
		printf("Minishell: %s: Permission denied\n", redirection->file);
		return (1);
	}
	if (append)
		process->fdout = open(redirection->file, \
					O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		process->fdout = open(redirection->file, \
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (process->fdout == -1)
		return (1);
	return (0);
}

static void	handler(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	exit(130);
}

static int	set_here_doc(t_process *process, t_lst_red *redirection)
{
	int		fd[2];
	int		pid;
	int		status;
	char	*str;

	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, &handler);
		str = get_next_line(STDIN_FILENO);
		if (!str)
			exit(print_return_error(\
			"minishell: here_doc exited with EOF!\n", 0, STDIN_FILENO));
		while (ft_strncmp(str, redirection->file, \
				ft_strlen(redirection->file) && \
				!(str[ft_strlen(redirection->file)] == '\n')))
		{
			write(fd[1], str, ft_strlen(str));
			free(str);
			str = get_next_line(STDIN_FILENO);
			if (!str)
			{
				close(fd[1]);
				exit(print_return_error(\
				"minishell: here_doc exited with EOF!\n", 0, STDIN_FILENO));
			}
		}
		free(str);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signalhandler_init();
	close(fd[1]);
	if (status)
	{
		close(fd[0]);
		process->data->exit_code = 130;
		return (1);
	}
	process->fdin = fd[0];
	return (0);
}

int	set_redirections(t_process *proc)
{
	t_lst_red	*temp;

	temp = *(proc->ls_red);
	while (temp)
	{
		if (temp->ambiguous_redirect)
		{
			ft_putstr_fd("Ambiguous redirect!\n", 1);
			temp = temp->next;
			continue ;
		}
		if (!ft_strncmp(temp->red, "<", 2) && set_in_red(proc, temp))
		{
			temp = temp->next;
			continue ;
		}
		if (!ft_strncmp(temp->red, ">", 2) && set_out_red(proc, temp, 0))
		{
			temp = temp->next;
			continue ;
		}
		if (!ft_strncmp(temp->red, ">>", 3) && set_out_red(proc, temp, 1))
		{
			temp = temp->next;
			continue ;
		}
		if (!ft_strncmp(temp->red, "<<", 3))
			return (set_here_doc(proc, temp));
		temp = temp->next;
	}
	return (0);
}
