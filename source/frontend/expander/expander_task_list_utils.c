/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_task_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:17:30 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 18:17:31 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

void	free_expander_task(t_expander_task *task)
{
	if (!task)
		return ;
	free(task->varname);
	free(task);
}

char	*get_varname(char *str)
{
	size_t	varname_len;

	varname_len = get_varname_len(str);
	return (ft_strndup(str, varname_len));
}

size_t	get_varname_len(char *str)
{
	size_t	len;

	len = 0;
	while (is_valid_varname_char(str[len]))
		len++;
	return (len);
}

t_expander_task	*init_expander_task(t_expander_task_type type, size_t start,
					size_t replace_len, char *str)
{
	t_expander_task	*task;

	task = (t_expander_task *)malloc(sizeof(t_expander_task));
	if (!task)
		return (NULL);
	task->type = type;
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

void	update_expander_tasks(t_list *task_list, size_t diff)
{
	t_expander_task	*task;

	while (task_list)
	{
		task = task_list->content;
		task->start += diff;
		task_list = task_list->next;
	}
}
