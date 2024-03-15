#include "expander.h"

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
	if (!check_null_expansion(lst, task_list))
		return (false);
	return (true);
}
