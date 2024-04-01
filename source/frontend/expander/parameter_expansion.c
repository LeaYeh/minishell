/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:18:15 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/30 11:40:37 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

bool	handle_parameter_expansion(t_list **task_list, t_shell *shell)
{
	bool			ret;
	t_expander_task	*task;
	t_list			*task_node;

	ret = true;
	task_node = *task_list;
	while (task_node && ret)
	{
		task = task_node->content;
		if (task->type == ET_VAR || task->type == ET_VAR_NO_SPLIT)
			ret = expand_variable(task_node, shell->env_list);
		else if (task->type == ET_EXIT_CODE)
			ret = expand_exit_code(task_node, shell->exit_code);
		if (task->type == ET_VAR_NO_SPLIT || task->type == ET_EXIT_CODE)
			ft_lstdrop_node(task_list, &task_node, (void *)free_expander_task);
		else
			task_node = task_node->next;
	}
	return (ret);
}

bool	expand_variable(t_list *task_node, t_list *env_list)
{
	int				diff_len;
	t_expander_task	*task;
	char			*value;

	task = task_node->content;
	value = get_value_from_env_list(env_list, task->varname);
	if (!value)
		value = "";
	if (!ft_strrplc_part(task->base_str, value, task->start, task->replace_len))
		return (false);
	task->result_len = ft_strlen(value);
	diff_len = task->result_len - task->replace_len;
	update_expander_tasks(task_node, diff_len, task->base_str);
	return (true);
}

bool	expand_exit_code(t_list *task_node, int exit_code)
{
	char			*exit_code_str;
	int				diff_len;
	t_expander_task	*task;

	task = task_node->content;
	exit_code_str = ft_itoa(exit_code);
	if (!exit_code_str)
		return (false);
	if (!ft_strrplc_part(
			task->base_str, exit_code_str, task->start, task->replace_len))
		return (free(exit_code_str), false);
	task->result_len = ft_strlen(exit_code_str);
	diff_len = task->result_len - task->replace_len;
	update_expander_tasks(task_node, diff_len, task->base_str);
	return (free(exit_code_str), true);
}
