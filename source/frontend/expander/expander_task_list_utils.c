/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_task_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:17:30 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/30 12:02:32 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

void	drop_task_types(
	t_list **task_list, char **word, t_expander_task_type type)
{
	t_expander_task	*task;
	t_list			*task_node;

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

void	free_expander_task(t_expander_task *task)
{
	if (!task)
		return ;
	free(task->varname);
	free(task);
}

t_expander_task	*init_expander_task(
	t_expander_task_type type, int start, int replace_len, char *str)
{
	t_expander_task	*task;

	task = (t_expander_task *)malloc(sizeof(t_expander_task));
	if (!task)
		return (NULL);
	task->type = type;
	task->base_str = NULL;
	task->start = start;
	task->replace_len = replace_len;
	if (type == ET_VAR || type == ET_VAR_NO_SPLIT)
	{
		task->varname = get_varname(str);
		if (!task->varname)
			return (free(task), NULL);
	}
	else
		task->varname = NULL;
	task->result_len = 0;
	return (task);
}

void	update_expander_tasks(t_list *task_list, int diff, char **new_base_str)
{
	char			**old_base_str;
	t_expander_task	*task;

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
