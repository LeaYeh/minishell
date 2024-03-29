/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:09:34 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/23 16:47:09 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	handle_quote_removal(t_list **task_list)
{
	t_list			*cur_task;
	t_expander_task	*task;

	cur_task = *task_list;
	while (cur_task)
	{
		task = cur_task->content;
		if (task->type == ET_QUOTE)
		{
			if (!remove_quote(cur_task))
				return (false);
			ft_lstdrop_node(task_list, &cur_task, (void *)free_expander_task);
		}
		else
			cur_task = cur_task->next;
	}
	return (true);
}

bool	remove_quote(t_list *task_list)
{
	int				diff_len;
	t_expander_task	*task;

	task = task_list->content;
	if (!ft_strrplc_part(task->base_str, "", task->start, task->replace_len))
		return (false);
	task->result_len = 0;
	diff_len = task->result_len - task->replace_len;
	update_expander_tasks(task_list, diff_len, task->base_str);
	return (true);
}
