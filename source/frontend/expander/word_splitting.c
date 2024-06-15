/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:17:46 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/30 11:49:31 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static bool	iter_word_splitting(t_list *expanded_list, t_list **task_list);
static bool	split_str_into_nodes(t_list **expanded_list, t_list *task_node);
static bool	split_node(
				t_list **expanded_list, t_list *task_node, int *i, int *end);

bool	handle_word_splitting(
			t_list **expanded_list, t_expd_op op_mask, t_list **task_list)
{
	if (op_mask & E_SPLIT_WORDS)
	{
		if (!iter_word_splitting(*expanded_list, task_list))
			return (false);
	}
	drop_null_expansion_nodes(expanded_list);
	return (true);
}

static bool	iter_word_splitting(t_list *expanded_list, t_list **task_list)
{
	t_expd_tsk	*task;
	t_list		*task_node;

	task_node = *task_list;
	while (task_node)
	{
		task = task_node->content;
		if (task->type == ET_VAR)
		{
			if (!split_str_into_nodes(&expanded_list, task_node))
				return (false);
			ft_lstdrop_node(task_list, &task_node, (void *)free_expander_task);
		}
		else
			task_node = task_node->next;
	}
	return (true);
}

static bool	split_str_into_nodes(t_list **expanded_list, t_list *task_node)
{
	char		**base_str;
	int			end;
	int			i;
	t_expd_tsk	*task;

	base_str = (char **)&(*expanded_list)->content;
	task = task_node->content;
	end = task->start + task->result_len;
	i = task->start;
	while (i < end)
	{
		if (ft_strchr(WORD_SEPERATORS, (*base_str)[i]))
		{
			if (!split_node(expanded_list, task_node, &i, &end))
				return (false);
			*expanded_list = (*expanded_list)->next;
			base_str = (char **)&(*expanded_list)->content;
		}
		else
			i++;
	}
	return (true);
}

static bool	split_node(
				t_list **expanded_list, t_list *task_node, int *i, int *end)
{
	char	**base_str;
	char	*rest;
	int		trimmed_len;

	base_str = (char **)&(*expanded_list)->content;
	rest = split_base_str(base_str, i, end);
	if (!rest)
		return (false);
	trimmed_len = trim_front_whitespace(&rest, i, end);
	if (trimmed_len == -1)
		return (free(rest), false);
	trimmed_len += ft_strlen(*base_str);
	if (!append_rest_to_list(expanded_list, task_node, rest, trimmed_len))
		return (free(rest), false);
	return (true);
}
