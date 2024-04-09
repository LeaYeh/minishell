/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_task_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:17:30 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/01 02:02:51 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	any_task_of_type(t_list *task_list, t_expd_tsk_typ type)
{
	t_expd_tsk	*task;

	while (task_list)
	{
		task = task_list->content;
		if (task->type == type)
			return (true);
		task_list = task_list->next;
	}
	return (false);
}

void	drop_task_types(
			t_list **task_list, char **word, t_expd_tsk_typ type)
{
	t_expd_tsk	*task;
	t_list		*task_node;

	task_node = *task_list;
	while (task_node)
	{
		task = task_node->content;
		if ((!word || task->base_str == word) && (!type || task->type == type))
			ft_lstdrop_node(task_list, &task_node, (void *)free_expander_task);
		else
			task_node = task_node->next;
	}
}

t_list	*get_expander_task_node(
			t_list *task_list, char **base_str, int i, t_expd_tsk_typ type)
{
	t_expd_tsk	*task;

	while (task_list)
	{
		task = task_list->content;
		if (task->type == type && task->base_str == base_str && \
			i >= task->start && i < task->start + task->replace_len)
			return (task_list);
		task_list = task_list->next;
	}
	return (NULL);
}

void	update_expander_tasks(
			t_list *task_list, int diff, char **new_base_str)
{
	char		**old_base_str;
	t_expd_tsk	*task;

	if (!task_list)
		return ;
	task = task_list->content;
	old_base_str = task->base_str;
	task_list = task_list->next;
	while (task_list)
	{
		task = task_list->content;
		if (task->base_str != old_base_str)
			break ;
		task->base_str = new_base_str;
		task->start += diff;
		task_list = task_list->next;
	}
}
