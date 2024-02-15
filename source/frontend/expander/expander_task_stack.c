#include "expander.h"
#include "utils.h"

t_expander_task	*init_expander_task(t_expander_task_type type, size_t start, size_t len)
{
	t_expander_task	*task;

	task = (t_expander_task *)malloc(sizeof(t_expander_task));
	if (!task)
		return (NULL);
	task->start = start;
	task->len = len;
	task->type = type;
	return (task);
}

bool	push_quote_task(t_list **task_stack, char *new_str, size_t *i)
{
	t_expander_task	*task;

	if ((new_str[*i] == '"' && !is_open_pair('\'', OP_GET)) || \
		(new_str[*i] == '\'' && !is_open_pair('"', OP_GET)))
	{
		task = init_expander_task(ET_QUOTE, *i, 1);
		if (!task || !ft_lstnew_front(task_stack, task))
			return (free(task), false);
		is_open_pair(new_str[*i], OP_SET);
	}
	return ((*i)++, true);
}

bool	push_parameter_task(t_list **task_stack, char *new_str, size_t *i)
{
	size_t					offset;
	size_t					replace_len;
	t_expander_task			*task;
	t_expander_task_type	type;

	replace_len = get_replace_len(&new_str[*i]);
	if (is_open_pair('\'', OP_GET))
		return (*i += replace_len, true);
	offset = get_offset(&new_str[*i]);
	if (is_valid_varname_start(new_str[*i + offset]))
		type = ET_VAR;
	else if (new_str[*i + offset] == '?')
		type = ET_EXIT_CODE;
	else
		return (*i += replace_len, true);
	task = init_expander_task(type, *i, replace_len);
	if (!task || !ft_lstnew_front(task_stack, task))
		return (free(task), false);
	return (*i += replace_len, true);
}

bool	create_expander_task_stack(t_list **task_stack, char *new_str, \
									t_expander_op op_mask)
{
	size_t	i;
	bool	ret;

	ret = true;
	i = 0;
	while (new_str[i] && ret)
	{
		if (ft_strchr(QUOTES, new_str[i]) && op_mask & E_RM_QUOTES)
			ret = push_quote_task(task_stack, new_str, &i);
		else if (new_str[i] == '$' && op_mask & (E_EXPAND | E_HEREDOC))
			ret = push_parameter_task(task_stack, new_str, &i);
		else
			i++;
		skip_to_expander_symbol(new_str, &i);
	}
	return (is_open_pair(0, OP_CLEAN), ret);
}
