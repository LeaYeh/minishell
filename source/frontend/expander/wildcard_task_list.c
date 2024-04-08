/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_task_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:42:00 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/31 13:42:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

static bool	iter_base_str(
				t_list **new_task_list,
				t_list **old_task_list,
				char **base_str);
static bool	append_wildcard_task(t_list **task_list, char **base_str, int *i);

bool	set_wildcard_task_list(
			t_list **task_list, t_list *expanded_list, t_expd_op op_mask)
{
	char	**base_str;
	t_list	*new_task_list;
	bool	ret;

	if (!(op_mask & E_WILDCARD))
		return (true);
	ret = true;
	new_task_list = NULL;
	while (expanded_list && ret)
	{
		base_str = (char **)&expanded_list->content;
		ret = iter_base_str(&new_task_list, task_list, base_str);
		expanded_list = expanded_list->next;
	}
	ft_lstadd_front(task_list, new_task_list);
	return (ret);
}

static bool	iter_base_str(
				t_list **new_task_list,
				t_list **old_task_list,
				char **base_str)
{
	int		i;
	bool	ret;

	ret = true;
	i = 0;
	while ((*base_str)[i] && ret)
	{
		if (ft_strchr(QUOTES, (*base_str)[i]) && \
			get_expander_task_node(*old_task_list, base_str, i, ET_QUOTE))
		{
			is_open_pair((*base_str)[i], OP_SET);
			ft_lstadd_back(new_task_list, ft_lstpop_front(old_task_list));
		}
		else if ((*base_str)[i] == '*')
		{
			ret = append_wildcard_task(new_task_list, base_str, &i);
			continue ;
		}
		i++;
	}
	is_open_pair(0, OP_CLEAN);
	return (ret);
}

static bool	append_wildcard_task(t_list **task_list, char **base_str, int *i)
{
	int			replace_len;
	t_expd_tsk	*task;

	replace_len = get_replace_len(&(*base_str)[*i]);
	if (is_open_pair('\'', OP_GET) || is_open_pair('"', OP_GET))
		return (*i += replace_len, true);
	task = init_expander_task(ET_WILDCARD, *i, replace_len, &(*base_str)[*i]);
	if (!task || !ft_lstnew_back(task_list, task))
		return (free_expander_task(task), false);
	task->base_str = base_str;
	return (*i += replace_len, true);
}
