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

static bool	expand_variable(t_list *task_node, t_list *env_list);
static bool	expand_special_variable(t_list *task_node, t_sh *shell);

bool	handle_parameter_expansion(t_list **task_list, t_sh *shell)
{
	bool		ret;
	t_expd_tsk	*task;
	t_list		*task_node;

	ret = true;
	task_node = *task_list;
	while (task_node && ret)
	{
		task = task_node->content;
		if (task->type == ET_VAR || task->type == ET_VAR_NO_SPLIT)
			ret = expand_variable(task_node, shell->env_list);
		else if (task->type == ET_EXIT_CODE || task->type == ET_SHELL_PID)
			ret = expand_special_variable(task_node, shell);
		if (task->type == ET_VAR_NO_SPLIT || task->type == ET_EXIT_CODE || \
			task->type == ET_SHELL_PID)
			ft_lstdrop_node(task_list, &task_node, (void *)free_expander_task);
		else
			task_node = task_node->next;
	}
	return (ret);
}

static bool	expand_variable(t_list *task_node, t_list *env_list)
{
	int			diff_len;
	t_expd_tsk	*task;
	char		*value;

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

static bool	expand_special_variable(t_list *task_node, t_sh *shell)
{
	int			diff_len;
	char		*special_var_string;
	t_expd_tsk	*task;

	task = task_node->content;
	special_var_string = NULL;
	if (task->type == ET_EXIT_CODE)
		special_var_string = ft_itoa(shell->exit_code);
	else if (task->type == ET_SHELL_PID)
		special_var_string = ft_itoa(shell->pid);
	if (!special_var_string)
		return (false);
	if (!ft_strrplc_part(
			task->base_str, special_var_string, task->start, task->replace_len))
		return (free(special_var_string), false);
	task->result_len = ft_strlen(special_var_string);
	diff_len = task->result_len - task->replace_len;
	update_expander_tasks(task_node, diff_len, task->base_str);
	return (free(special_var_string), true);
}
