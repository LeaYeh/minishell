#include "defines.h"
#include "utils.h"
#include "clean.h"

void	handle_assignment(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	final_cmd_table->cmd_name = ft_strdup("set");
	if (!final_cmd_table->cmd_name)
	{
		free_final_cmd_table(&final_cmd_table);
		ft_clean_and_exit_shell(
			shell, GENERAL_ERROR, "handle_assignment failed");
	}
}
