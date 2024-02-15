#include "expander.h"

bool	expand(char **new_str, t_list **lst, t_shell *shell,
			t_expander_op op_mask)
{
	t_list	*task_stack;

	task_stack = NULL;
	if (!create_expander_task_stack(&task_stack, *new_str, op_mask) || \
		!execute_expander_task_stack(new_str, task_stack, lst, shell))
		return (ft_lstclear(&task_stack, free), false);
	if (is_null_expansion(*new_str, task_stack))
		ft_free_and_null((void **)new_str);
	ft_lstclear(&task_stack, free);
	return (true);
}

bool	execute_expander_task_stack(char **new_str, t_list *task_stack,
			t_list **lst, t_shell *shell)
{
	bool			ret;
	t_expander_task	*task;

	(void)lst;
	ret = true;
	while (task_stack && ret)
	{
		task = task_stack->content;
		if (task->type == ET_VAR)
			ret = expand_variable(new_str, task, shell->env_list);
		else if (task->type == ET_EXIT_CODE)
			ret = expand_exit_code(new_str, task, shell->exit_code);
		else if (task->type == ET_QUOTE)
			ret = remove_quote(new_str, task);
		task_stack = task_stack->next;
	}
	return (ret);
}

bool	is_null_expansion(char *new_str, t_list *task_stack)
{
	t_expander_task	*task;

	if (new_str[0])
		return (false);
	while (task_stack)
	{
		task = task_stack->content;
		if (task->type == ET_QUOTE)
			return (false);
		task_stack = task_stack->next;
	}
	return (true);
}
