#include "expander.h"

bool	expand(
	char **new_str, t_list **lst, t_shell *shell, t_expander_op op_mask)
{
	t_list	*task_list;

	task_list = NULL;
	if (!create_expander_task_list(&task_list, *new_str, op_mask) || \
		!execute_expander_task_list(new_str, task_list, shell) || \
		!split_words(lst, new_str, task_list))
		return (ft_lstclear(&task_list, (void *)free_expander_task), false);
	// if (is_null_expansion(*new_str, task_list))
	// 	ft_free_and_null((void **)new_str);
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
	// if (ret)
		// ret = ft_lstnew_back(lst, *new_str);
	return (ret);
}

bool	is_null_expansion(char *new_str, t_list *task_list)
{
	t_expander_task	*task;

	if (new_str[0])
		return (false);
	while (task_list)
	{
		task = task_list->content;
		if (task->type == ET_QUOTE)
			return (false);
		task_list = task_list->next;
	}
	return (true);
}
