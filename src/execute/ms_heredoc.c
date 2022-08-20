/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:57:57 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/20 16:14:09 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handler(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	exit(130);
}

static void	inputloop(int *pipe, char **str)
{
	write(pipe[1], *str, ft_strlen(*str));
	free(*str);
	write(STDOUT_FILENO, "> ", 2);
	*str = get_next_line(STDIN_FILENO);
	if (!(*str))
	{
		close(pipe[1]);
		exit(print_return_error(\
		"minishell: here_doc exited with EOF!\n", 1, STDERR_FILENO));
	}
}

static void	execute_child(t_process *proc, t_lst_red *red, int *pipe)
{
	char	*str;

	process_fds_close(proc->data, -1);
	pipes_close(proc->data, -1);
	close(pipe[0]);
	signal(SIGINT, &handler);
	write(STDOUT_FILENO, "> ", 2);
	str = get_next_line(STDIN_FILENO);
	if (!str)
	{
		close(pipe[1]);
		exit(print_return_error(\
		"minishell: here_doc exited with EOF!\n", 1, STDERR_FILENO));
	}
	while (ft_strncmp(str, red->file, ft_strlen(red->file)) \
			|| str[strlen(red->file)] != '\n' \
			|| str[strlen(red->file) + 1] != '\0')
		inputloop(pipe, &str);
	close(pipe[1]);
	free(str);
	exit(0);
}

static int	exit_status(int status, t_process *process, int pipe_fdin)
{
	if (status == 33280)
	{
		close(pipe_fdin);
		process->data->exit_code = 130;
		return (1);
	}
	else
	{
		close(pipe_fdin);
		process->data->exit_code = 0;
		return (0);
	}
}

int	set_here_doc(t_process *process, t_lst_red *redirection)
{
	int		fd[2];
	int		pid;
	int		status;

	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (!pid)
		execute_child(process, redirection, fd);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signalhandler_init();
	if (status)
		return (exit_status(status, process, fd[0]));
	if (process->fdin != 0 \
		|| (process->data->n_processes > 1 && process->fdin != 0))
		close(process->fdin);
	process->fdin = fd[0];
	return (0);
}
