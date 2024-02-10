#include "defines.h"
#include "utils.h"
#include "clean.h"
#include "export.h"

// TODO: Add the assignments to the local shell variables list
// TODO: Also add flags if a variable is exported or not

// If !shell->final_cmd_table->simple_cmd[0], then V_EXPORT_NO
// Else, V_TEMP
bool	handle_assignment(t_shell *shell)
{
	char		**assignment_array;
	int			i;
	t_env_state	state;

	assignment_array = shell->final_cmd_table->assignment_array;
	if (!assignment_array)
		return (true);
	printf("handle_assignment\n");
	if (!shell->final_cmd_table->simple_cmd[0])
		state = V_EXPORT_NO;
	else
		state = V_TEMP;
	i = 0;
	while (assignment_array[i])
	{
		printf("assignment_array[%d]: %s\n", i, assignment_array[i]);
		if (!handle_var_export(assignment_array[i], &shell->env_list, state))
			return (false);
		i++;
	}
	return (true);
}

void	remove_temp_env_vars(t_list **env_list)
{
	t_list	*cur;
	t_env	*env_node;

	cur = *env_list;
	while (cur)
	{
		env_node = cur->content;
		if (env_node->state == V_TEMP)
			// Should restore to what it was previously, not always drop.
			ft_lstdrop_node(env_list, &cur, (void *)free_env_node);
		else
			cur = cur->next;
	}
}
