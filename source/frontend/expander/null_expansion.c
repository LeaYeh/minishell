#include "expander.h"

static bool	is_null_expansion(char *str, t_list *task_list)
{
	t_expander_task	*task;

	if (str && *str)
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

void	check_null_expansions(t_list **lst, t_list *task_list)
{
	t_list	*cur;

	cur = *lst;
	while (cur)
	{
		if (is_null_expansion(cur->content, task_list))
			ft_lstdrop_node(lst, &cur, free);
		else
			cur = cur->next;
	}
}
