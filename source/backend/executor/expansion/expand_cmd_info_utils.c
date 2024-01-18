#include "executor.h"
#include "expander.h"
#include "utils.h"

// after expander if cmd_name => NULL, the cmd_name should be replace by the first non-null argument
// 	cmd_args need to filter out the NULL
// => Maybe combine the cmd_name and cmd_args into one list in a function and pass to expander 1-1 then separate back
// if the executor receives "1 2 3" as cmd_name, it should be split into "1" "2" "3"
int	handle_expand_error(t_list **expanded_list, char **str_array, int i)
{
	int	ret;

	if (!str_array[i])
		ret = GENERAL_ERROR;
	else
		ret = EXPAND_ERROR;
	free_array(str_array);
	ft_lstclear(expanded_list, free);
	return (ret);
}

bool	append_expanded_array(char ***expanded_array, t_list *expanded_list)
{
	char	**tmp;
	int		i;

	tmp = (char **)ft_calloc(
			get_array_len(*expanded_array) + ft_lstsize(expanded_list) + 1,
			sizeof(char *));
	if (!tmp)
		return (false);
	i = 0;
	while (*expanded_array && (*expanded_array)[i])
	{
		tmp[i] = ft_strdup((*expanded_array)[i]);
		if (!tmp[i++])
			return (free_array(tmp), false);
	}
	while (expanded_list)
	{
		if (expanded_list->content)
		{
			tmp[i] = ft_strdup(expanded_list->content);
			if (!tmp[i++])
				return (free_array(tmp), false);
		}
		expanded_list = expanded_list->next;
	}
	free_array(*expanded_array);
	*expanded_array = tmp;
	return (true);
}

int	set_expanded_cmd_info(
	t_shell *shell, t_final_cmd_table *final_cmd_table, char ***expanded_array)
{
	char	**cmd_info_array;
	t_list	*expanded_list;
	int		i;

	cmd_info_array = final_cmd_table->simple_cmd;
	expanded_list = NULL;
	i = 0;
	while (cmd_info_array[i])
	{
		// This is unsafe bc if ft_expander sets member in cmd_info_array to NULL, nothing after it will be freed anymore.
		if (!ft_expander(&cmd_info_array[i], &expanded_list, shell) || \
			!append_expanded_array(expanded_array, expanded_list))
			return (
				handle_expand_error(&expanded_list, cmd_info_array, i));
		ft_lstclear(&expanded_list, free);
		i++;
	}
	free_array(cmd_info_array);
	return (SUCCESS);
}
