#include "expander.h"
#include "utils.h"

bool	create_expander_task_list(t_list **task_list, char *new_str,
			t_expander_op op_mask)
{
	size_t	i;
	bool	ret;

	ret = true;
	i = 0;
	while (new_str[i] && ret)
	{
		if (ft_strchr(QUOTES, new_str[i]) && op_mask & E_RM_QUOTES)
			ret = append_quote_task(task_list, new_str, &i);
		else if (new_str[i] == '$' && op_mask & (E_EXPAND | E_HEREDOC))
			ret = append_parameter_task(task_list, new_str, &i, op_mask);
		else
			i++;
		skip_to_expander_symbol(new_str, &i);
	}
	return (is_open_pair(0, OP_CLEAN), ret);
}

bool	append_quote_task(t_list **task_list, char *new_str, size_t *i)
{
	t_expander_task	*task;

	if ((new_str[*i] == '"' && !is_open_pair('\'', OP_GET)) || \
		(new_str[*i] == '\'' && !is_open_pair('"', OP_GET)))
	{
		task = init_expander_task(ET_QUOTE, *i, 1, &new_str[*i]);
		if (!task || !ft_lstnew_back(task_list, task))
			return (free_expander_task(task), false);
		is_open_pair(new_str[*i], OP_SET);
	}
	return ((*i)++, true);
}

bool	append_parameter_task(t_list **task_list, char *new_str, size_t *i,
			t_expander_op op_mask)
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
	{
		if (!is_open_pair('"', OP_GET) && !(op_mask & E_HEREDOC))
			type = ET_VAR;
		else
			type = ET_VAR_NO_SPLIT;
	}
	else if (new_str[*i + offset] == '?')
		type = ET_EXIT_CODE;
	else
		return (*i += replace_len, true);
	task = init_expander_task(type, *i, replace_len, &new_str[*i + offset]);
	if (!task || !ft_lstnew_back(task_list, task))
		return (free_expander_task(task), false);
	return (*i += replace_len, true);
}
