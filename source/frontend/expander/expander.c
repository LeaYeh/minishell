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
	if (!handle_expansion(lst, &new_str, shell, op_mask))
		return (free(new_str), MALLOC_ERROR);
	return (SUCCESS);
}

bool	handle_expansion(t_list **lst, char **new_str, t_shell *shell,
			t_expander_op op_mask)
{
	t_list	*task_list;

	task_list = NULL;
	if (!set_expander_task_list(&task_list, *new_str, op_mask) || \
		!execute_expander_task_list(new_str, task_list, shell) || \
		!set_expanded_list(lst, new_str, op_mask, task_list))
		return (ft_lstclear(&task_list, (void *)free_expander_task), false);
	ft_lstclear(&task_list, (void *)free_expander_task);
	return (true);
}

bool	execute_expander_task_list(
	char **new_str, t_list *task_list, t_shell *shell)
{
	bool			ret;
	t_expander_task	*task;

	ret = true;
	while (task_list && ret)
	{
		task = task_list->content;
		if (task->type == ET_VAR || task->type == ET_VAR_NO_SPLIT)
			ret = expand_variable(new_str, task_list, shell->env_list);
		else if (task->type == ET_EXIT_CODE)
			ret = expand_exit_code(new_str, task_list, shell->exit_code);
		else if (task->type == ET_QUOTE)
			ret = remove_quote(new_str, task_list);
		update_expander_tasks(
			task_list->next, task->result_len - task->replace_len);
		task_list = task_list->next;
	}
	return (ret);
}

bool	set_expanded_list(
	t_list **lst, char **new_str, t_expander_op op_mask, t_list *task_list)
{
	if (op_mask & E_SPLIT_WORDS)
	{
		if (!split_words(lst, new_str, task_list))
			return (false);
	}
	else if (!ft_lstnew_back(lst, *new_str))
		return (false);
	check_null_expansions(lst, task_list);
	return (true);
}
