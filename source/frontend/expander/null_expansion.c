#include "expander.h"

static bool	is_null_expansion(t_list *lst, t_list *task_list)
{
	t_expander_task	*task;

	while (lst)
	{
		if (lst->content && *(char *)lst->content)
			return (false);
		lst = lst->next;
	}
	while (task_list)
	{
		task = task_list->content;
		if (task->type == ET_QUOTE)
			return (false);
		task_list = task_list->next;
	}
	return (true);
}

bool	check_null_expansion(t_list **lst, t_list *task_list)
{
	t_list	*tmp;

	if (is_null_expansion(*lst, task_list))
	{
		tmp = ft_lstnew(NULL);
		if (!tmp)
			return (false);
		ft_lstclear(lst, free);
		*lst = tmp;
	}
	return (true);
}
