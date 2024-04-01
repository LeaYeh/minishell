/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_task_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 02:00:05 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/01 02:00:27 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
	task->result_len = -1;
	return (task);
}
