/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_task_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:17:36 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 18:17:37 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

bool	set_parameter_expansion_info(
	t_list **task_list, char **base_str, t_expander_op op_mask)
{
	int		i;
	bool	ret;

	ret = true;
	i = 0;
	while ((*base_str)[i] && ret)
	{
		if (op_mask & E_RM_QUOTES && is_unquoted_quote((*base_str)[i]))
			is_open_pair((*base_str)[i], OP_SET);
		else if (op_mask & E_EXPAND && (*base_str)[i] == '$')
		{
			ret = append_parameter_task(task_list, base_str, &i, op_mask);
			continue ;
		}
		i++;
	}
	return (is_open_pair(0, OP_CLEAN), ret);
}

bool	append_parameter_task(
	t_list **task_list, char **base_str, int *i, t_expander_op op_mask)
{
	int						offset;
	int						replace_len;
	t_expander_task			*task;
	t_expander_task_type	type;

	replace_len = get_replace_len(&(*base_str)[*i]);
	if (is_open_pair('\'', OP_GET))
		return (*i += replace_len, true);
	offset = get_offset(&(*base_str)[*i]);
	if (is_valid_varname_start((*base_str)[*i + offset]))
	{
		if (op_mask & E_SPLIT_WORDS && !is_open_pair('"', OP_GET))
			type = ET_VAR;
		else
			type = ET_VAR_NO_SPLIT;
	}
	else if ((*base_str)[*i + offset] == '?')
		type = ET_EXIT_CODE;
	else
		return (*i += replace_len, true);
	task = init_expander_task(type, *i, replace_len, &(*base_str)[*i + offset]);
	if (!task || !ft_lstnew_back(task_list, task))
		return (free_expander_task(task), false);
	task->base_str = base_str;
	return (*i += replace_len, true);
}

bool	set_quote_wildcard_expansion_info(
	t_list **task_list, t_list *lst, t_expander_op op_mask)
{
	char	**base_str;
	int		i;
	bool	ret;

	ret = true;
	while (lst && ret)
	{
		base_str = (char **)&lst->content;
		i = 0;
		while ((*base_str)[i] && ret)
		{
			if (op_mask & E_RM_QUOTES && ft_strchr(QUOTES, (*base_str)[i]))
				ret = append_quote_task(task_list, base_str, &i);
			else if ((*base_str)[i] == '*')
				ret = append_wildcard_task(task_list, base_str, &i);
			else
				i++;
		}
		lst = lst->next;
	}
	return (is_open_pair(0, OP_CLEAN), ret);
}

bool	append_quote_task(t_list **task_list, char **base_str, int *i)
{
	t_expander_task	*task;

	if (is_unquoted_quote((*base_str)[*i]))
	{
		task = init_expander_task(ET_QUOTE, *i, 1, &(*base_str)[*i]);
		if (!task || !ft_lstnew_back(task_list, task))
			return (free_expander_task(task), false);
		task->base_str = base_str;
		is_open_pair((*base_str)[*i], OP_SET);
	}
	return ((*i)++, true);
}

bool	append_wildcard_task(t_list **task_list, char **base_str, int *i)
{
	t_expander_task	*task;
	int				replace_len;

	replace_len = get_replace_len(&(*base_str)[*i]);
	if (is_open_pair('\'', OP_GET) || is_open_pair('"', OP_GET))
		return (*i += replace_len, true);
	task = init_expander_task(ET_WILDCARD, *i, replace_len, &(*base_str)[*i]);
	if (!task || !ft_lstnew_back(task_list, task))
		return (free_expander_task(task), false);
	task->base_str = base_str;
	return (*i += replace_len, true);
}
