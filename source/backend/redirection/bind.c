#include "executor.h"
#include "utils.h"

bool	bind_to_stdio(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	bool	ret;

	if (dup2(final_cmd_table->read_fd, STDIN_FILENO) == -1 || \
		dup2(final_cmd_table->write_fd, STDOUT_FILENO) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: ", PROGRAM_NAME);
		perror(final_cmd_table->simple_cmd[0]);
		ret = false;
	}
	else
		ret = true;
	safe_close_pipe(&shell->new_pipe);
	safe_close_pipe(&shell->old_pipe);
	return (ret);
}
