/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_param_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:20:26 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/23 16:47:31 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	expand_exit_code(t_list *task_list, int exit_code)
{
	char			*exit_code_str;
	int				diff_len;
	t_expander_task	*task;

	task = task_list->content;
	exit_code_str = ft_itoa(exit_code);
	if (!exit_code_str)
		return (false);
	if (!ft_strrplc_part(
			task->base_str, exit_code_str, task->start, task->replace_len))
		return (free(exit_code_str), false);
	task->result_len = ft_strlen(exit_code_str);
	diff_len = task->result_len - task->replace_len;
	update_expander_tasks(task_list, diff_len, task->base_str);
	return (free(exit_code_str), true);
}
