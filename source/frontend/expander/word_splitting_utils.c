/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:41:12 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/25 18:43:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*split_base_str(char **base_str, int *i, int *end)
{
	char	**halves;
	char	*rest;

	halves = ft_split_at_index(*base_str, *i);
	if (!halves)
		return (NULL);
	free(*base_str);
	*base_str = halves[0];
	rest = halves[1];
	free(halves);
	*end -= *i;
	*i = 0;
	return (rest);
}

int	trim_front_whitespace(char **base_str, int *i, int *end)
{
	int	trimmed_len;

	while (ft_strchr(WORD_SEPERATORS, (*base_str)[*i]) && *i < *end)
		(*i)++;
	if (!ft_strrplc_part(base_str, "", 0, *i))
		return (-1);
	trimmed_len = *i;
	*end -= trimmed_len;
	*i = 0;
	return (trimmed_len);
}

bool	append_rest_to_list(
			t_list **expanded_list,
			t_list *task_node,
			char *rest,
			int trimmed_len)
{
	char		**new_base_str;
	t_list		*new_node;
	t_expd_tsk	*task;

	task = task_node->content;
	new_node = ft_lstnew(rest);
	if (!new_node)
		return (false);
	ft_lstadd_back(expanded_list, new_node);
	new_base_str = (char **)&new_node->content;
	update_expander_tasks(task_node, 0 - trimmed_len, new_base_str);
	task->base_str = new_base_str;
	return (true);
}
