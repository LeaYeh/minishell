/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:18:15 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/28 02:12:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

// static	bool	all_ifs(char *str)
// {
// 	while (*str)
// 	{
// 		if (!ft_strchr(" \t\n", *str))
// 			return (false);
// 		str++;
// 	}
// 	return (true);
// }

static char	*cut(char **new_str, size_t *i, size_t *end)
{
	char	**halves;
	char	*result;

	halves = ft_split_at_index(*new_str, *i);
	if (!halves)
		return (NULL);
	result = halves[0];
	free(*new_str);
	*new_str = halves[1];
	free(halves);
	*end -= *i;
	*i = 0;
	while (ft_strchr(" \t\n", (*new_str)[*i]) && *i < *end)
		(*i)++;
	if (!ft_strrplc_part(new_str, "", 0, *i))
		return (free(result), NULL);
	*end -= *i;
	*i = 0;
	return (result);
}

bool	handle_split(char **new_str, t_list *task_list, t_list **lst)
{
	size_t			end;
	size_t			i;
	char			*result;
	t_expander_task	*task;

	task = task_list->content;
	end = task->start + task->result_len;
	i = task->start;
	while (i < end)
	{
		if (ft_strchr(" \t\n", (*new_str)[i]))
		{
			result = cut(new_str, &i, &end);
			if (!result)
				return (false);
			if (!ft_lstnew_back(lst, result))
				return (free(result), false);
			update_expander_tasks(task_list, 0 - ft_strlen(result));
		}
		else
			i++;
	}
	return (true);
}

bool	split_words(t_list **lst, char **new_str, t_list *task_list)
{
	t_expander_task	*task;

	while (task_list)
	{
		task = task_list->content;
		if (task->type == ET_VAR)
		{
			if (!handle_split(new_str, task_list, lst))
				return (false);
		}
		task_list = task_list->next;
	}
	return (ft_lstnew_back(lst, *new_str));
}

bool	expand_variable(char **new_str, t_list *task_list, t_list *env_list)
{
	t_expander_task	*task;
	char			*value;

	task = task_list->content;
	value = get_value_from_env_list(env_list, task->varname);
	if (!value)
		value = "";
	task->result_len = ft_strlen(value);
	if (!ft_strrplc_part(new_str, value, task->start, task->replace_len))
		return (false);
	task->result_len = ft_strlen(value);
	return (true);
}
