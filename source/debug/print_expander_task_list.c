/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expander_task_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 11:46:08 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/31 13:41:24 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "expander.h"

bool	print_expander_task_list(t_list *task_list, char *calling_function)
{
	ft_dprintf(STDERR_FILENO, "\n");
	if (calling_function)
		ft_dprintf(STDERR_FILENO, STY_BOL "%s:\n" STY_RES, calling_function);
	if (!task_list)
	{
		ft_dprintf(STDERR_FILENO, "----- Empty expander task list -----\n");
		ft_dprintf(STDERR_FILENO, "------------------------------------\n\n");
		return (true);
	}
	ft_dprintf(STDERR_FILENO, "-------- Expander Task List --------\n");
	while (task_list)
	{
		if (!print_expander_task_node(task_list))
			return (false);
		task_list = task_list->next;
		if (task_list)
			ft_dprintf(STDERR_FILENO, "----------------------\n");
	}
	ft_dprintf(STDERR_FILENO, "------------------------------------\n\n");
	return (true);
}

bool	print_expander_task_node(t_list *task_node)
{
	t_expd_tsk	*task;
	char		*to_be_replaced;

	task = (t_expd_tsk *)task_node->content;
	to_be_replaced = (char *)malloc((task->replace_len + 1) * sizeof(char));
	if (!to_be_replaced)
		return (false);
	ft_snprintf(to_be_replaced,
		task->replace_len + 1, "%s", &(*task->base_str)[task->start]);
	ft_dprintf(STDERR_FILENO, "Task type:        %s\n",
		get_expander_task_type_name(task->type));
	ft_dprintf(STDERR_FILENO, "Base string:      %s\n", *(task->base_str));
	ft_dprintf(STDERR_FILENO, "Start:            %d\n", task->start);
	ft_dprintf(STDERR_FILENO, "  From start:     %s\n",
		&(*task->base_str)[task->start]);
	ft_dprintf(STDERR_FILENO, "Replace length:   %d\n", task->replace_len);
	ft_dprintf(STDERR_FILENO, "  To be replaced: %s\n", to_be_replaced);
	ft_dprintf(STDERR_FILENO, "Varname:          %s\n", task->varname);
	ft_dprintf(STDERR_FILENO, "Result length:    %d\n", task->result_len);
	free(to_be_replaced);
	return (true);
}

char	*get_expander_task_type_name(t_expd_tsk_typ type)
{
	const char	*task_type_names[] = {
		"ET_VAR",
		"ET_VAR_NO_SPLIT",
		"ET_EXIT_CODE",
		"ET_SHELL_PID",
		"ET_WILDCARD",
		"ET_QUOTE"
	};

	return ((char *)task_type_names[type]);
}
