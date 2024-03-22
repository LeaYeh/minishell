/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 09:43:44 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/21 17:36:47 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	expander(char *str, t_list **lst, t_shell *shell, t_expander_op op_mask)
{
	char	*new_str;

	if (!str)
		return (SUCCESS);
	new_str = ft_strdup(str);
	if (!new_str)
		return (MALLOC_ERROR);
	if (is_bad_substitution(new_str, op_mask))
		return (free(new_str), BAD_SUBSTITUTION);
	if (!ft_lstnew_back(lst, new_str))
		return (free(new_str), MALLOC_ERROR);
	if (!handle_expansion(lst, shell, op_mask))
		return (MALLOC_ERROR);
	expand_wildcard(new_str);
	return (SUCCESS);
}

bool	handle_expansion(t_list **lst, t_shell *shell, t_expander_op op_mask)
{
	char	**base_str;
	t_list	*task_list;

	base_str = (char **)&(*lst)->content;
	task_list = NULL;
	if (!set_expander_task_list(&task_list, base_str, op_mask) || \
		!handle_parameter_expansion(task_list, shell) || \
		!set_expanded_list(lst, op_mask, &task_list) || \
		!handle_quote_removal(task_list))
		return (ft_lstclear(&task_list, (void *)free_expander_task), false);
	ft_lstclear(&task_list, (void *)free_expander_task);
	return (true);
}

bool	handle_parameter_expansion(t_list *task_list, t_shell *shell)
{
	bool			ret;
	t_expander_task	*task;

	ret = true;
	while (task_list && ret)
	{
		task = task_list->content;
		if (task->type == ET_VAR || task->type == ET_VAR_NO_SPLIT)
			ret = expand_variable(task_list, shell->env_list);
		else if (task->type == ET_EXIT_CODE)
			ret = expand_exit_code(task_list, shell->exit_code);
		task_list = task_list->next;
	}
	return (ret);
}

bool	set_expanded_list(
	t_list **lst, t_expander_op op_mask, t_list **task_list)
{
	if (op_mask & E_SPLIT_WORDS)
	{
		if (!handle_word_splitting(*lst, task_list))
			return (false);
	}
	drop_null_expansion_nodes(lst);
	return (true);
}
