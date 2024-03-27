/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:18:15 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/23 16:47:34 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

bool	expand_variable(t_list *task_list, t_list *env_list)
{
	int				diff_len;
	t_expander_task	*task;
	char			*value;

	task = task_list->content;
	value = get_value_from_env_list(env_list, task->varname);
	if (!value)
		value = "";
	if (!ft_strrplc_part(task->base_str, value, task->start, task->replace_len))
		return (false);
	task->result_len = ft_strlen(value);
	diff_len = task->result_len - task->replace_len;
	update_expander_tasks(task_list, diff_len, task->base_str);
	return (true);
}
