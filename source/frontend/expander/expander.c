/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 09:43:44 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/28 22:20:27 by ldulling         ###   ########.fr       */
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
	return (SUCCESS);
}

bool	handle_expansion(t_list **lst, t_shell *shell, t_expander_op op_mask)
{
	char	**base_str;
	t_list	*task_list;

	base_str = (char **)&(*lst)->content;
	task_list = NULL;
	if (!set_expander_task_list(&task_list, base_str, op_mask) || \
		!handle_parameter_expansion(&task_list, shell) || \
		!set_expanded_list(lst, op_mask, &task_list) || \
		!handle_wildcard_expansion(lst) || \
		!handle_quote_removal(&task_list))
		return (ft_lstclear(&task_list, (void *)free_expander_task), false);
	ft_lstclear(&task_list, (void *)free_expander_task);
	return (true);
}

bool	handle_parameter_expansion(t_list **task_list, t_shell *shell)
{
	t_list			*cur_task;
	bool			ret;
	t_expander_task	*task;

	ret = true;
	cur_task = *task_list;
	while (cur_task && ret)
	{
		task = cur_task->content;
		if (task->type == ET_VAR || task->type == ET_VAR_NO_SPLIT)
			ret = expand_variable(cur_task, shell->env_list);
		else if (task->type == ET_EXIT_CODE)
			ret = expand_exit_code(cur_task, shell->exit_code);
		if (task->type == ET_VAR_NO_SPLIT || task->type == ET_EXIT_CODE)
			ft_lstdrop_node(task_list, &cur_task, (void *)free_expander_task);
		else
			cur_task = cur_task->next;
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
