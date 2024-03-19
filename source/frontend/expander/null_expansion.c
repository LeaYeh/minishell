/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:17:40 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 18:17:41 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static bool	is_null_expansion(char *str)
{
	if (!str || !*str)
		return (true);
	return (false);
}

static bool	any_quote_task(t_list *task_list)
{
	t_expander_task	*task;

	while (task_list)
	{
		task = task_list->content;
		if (task->type == ET_QUOTE)
			return (true);
		task_list = task_list->next;
	}
	return (false);
}

void	check_null_expansions(t_list **lst, t_list *task_list)
{
	t_list	*cur;

	if (any_quote_task(task_list))
		return ;
	cur = *lst;
	while (cur)
	{
		if (is_null_expansion(cur->content))
			ft_lstdrop_node(lst, &cur, free);
		else
			cur = cur->next;
	}
}
