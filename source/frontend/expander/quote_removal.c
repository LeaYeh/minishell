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
	t_expander_task	*task;
	t_list			*task_node;

	task_node = *task_list;
	while (task_node)
	{
		task = task_node->content;
		if (task->type == ET_QUOTE)
		{
			if (!remove_quote(task_node))
				return (false);
			ft_lstdrop_node(task_list, &task_node, (void *)free_expander_task);
		}
		else
			task_node = task_node->next;
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
