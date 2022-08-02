/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:01:04 by lschrafs          #+#    #+#             */
/*   Updated: 2022/08/02 16:32:09 by lschrafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*static void	e_a_s_red(t_process *ret)
{
	t_lst_env	*temp;

	temp = *(ret->ls_red);
	while (temp)
	{
		str_expand(temp->value);
		temp = temp->next;
	}
	temp = *(ret->ls_red);
	while (temp)
	{
		str_remove_quotes(temp->value);
		temp = temp->next;
	}
}*/

void	expand_and_sort(t_process *ret)
{
	(void) ret;
	//e_a_s_red(ret);
	//e_a_s_cmd(ret);
}
