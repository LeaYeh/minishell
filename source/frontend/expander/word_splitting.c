/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:17:46 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/25 18:41:09 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static bool	split_node(t_list **lst, t_list *task_list, int *i, int *end)
{
	char	**base_str;
	char	*rest;
	int		trimmed_len;

	base_str = (char **)&(*lst)->content;
	rest = split_base_str(base_str, i, end);
	if (!rest)
		return (false);
	trimmed_len = trim_front_whitespace(&rest, i, end);
	if (trimmed_len == -1)
		return (free(rest), false);
	trimmed_len += ft_strlen(*base_str);
	if (!append_rest_to_list(lst, task_list, rest, trimmed_len))
		return (free(rest), false);
	return (true);
}

static bool	split_str_into_nodes(t_list **lst, t_list *task_list)
{
	char			**base_str;
	int				end;
	int				i;
	t_expander_task	*task;

	base_str = (char **)&(*lst)->content;
	task = task_list->content;
	end = task->start + task->result_len;
	i = task->start;
	while (i < end)
	{
		if (ft_strchr(WORD_SEPERATORS, (*base_str)[i]))
		{
			if (!split_node(lst, task_list, &i, &end))
				return (false);
			*lst = (*lst)->next;
			base_str = (char **)&(*lst)->content;
		}
		else
			i++;
	}
	return (true);
}

bool	handle_word_splitting(t_list *lst, t_list **task_list)
{
	t_expander_task	*task;
	t_list			*task_node;

	task_node = *task_list;
	while (task_node)
	{
		task = task_node->content;
		if (task->type == ET_VAR)
		{
			if (!split_str_into_nodes(&lst, task_node))
				return (false);
			ft_lstdrop_node(task_list, &task_node, (void *)free_expander_task);
		}
		else
			task_node = task_node->next;
	}
	return (true);
}
