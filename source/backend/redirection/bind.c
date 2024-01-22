#include "executor.h"
#include "utils.h"
#include "clean.h"

void	bind_to_stdio(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	if (dup2(final_cmd_table->read_fd, STDIN_FILENO) == -1 || \
		dup2(final_cmd_table->write_fd, STDOUT_FILENO) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: ", PROGRAM_NAME);
		perror(final_cmd_table->simple_cmd[0]);
		safe_close_pipe(&shell->new_pipe);
		safe_close_pipe(&shell->old_pipe);
		free_final_cmd_table(&final_cmd_table);
		ft_clean_and_exit_shell(shell, SUBSHELL_ERROR, NULL);
	}
	safe_close_pipe(&shell->new_pipe);
	safe_close_pipe(&shell->old_pipe);
}
