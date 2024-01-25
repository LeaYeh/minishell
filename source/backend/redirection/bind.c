#include "executor.h"
#include "utils.h"

bool	save_std_io(int saved_std_io[2])
{
	saved_std_io[0] = dup(STDIN_FILENO);
	saved_std_io[1] = dup(STDOUT_FILENO);
	if (saved_std_io[0] == -1 || saved_std_io[1] == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: ", PROGRAM_NAME);
		perror(NULL);
		safe_close(&saved_std_io[0]);
		safe_close(&saved_std_io[1]);
		return (false);
	}
	return (true);
}

bool	redirect_io(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	bool	ret;

	ret = true;
	if (dup2(final_cmd_table->read_fd, STDIN_FILENO) == -1 || \
		dup2(final_cmd_table->write_fd, STDOUT_FILENO) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: ", PROGRAM_NAME);
		perror(NULL);
		ret = false;
	}
	if (shell->subshell_level != 0)
	{
		safe_close_all_pipes(shell);
		safe_close(&final_cmd_table->read_fd);
		safe_close(&final_cmd_table->write_fd);
	}
	return (ret);
}

bool	restore_std_io(int saved_std_io[2])
{
	bool	error;

	error = false;
	if (saved_std_io[0] != -1)
		if (dup2(saved_std_io[0], STDIN_FILENO) == -1)
			error = true;
	if (!error && saved_std_io[1] != -1)
		if (dup2(saved_std_io[1], STDOUT_FILENO) == -1)
			error = true;
	if (error)
	{
		ft_dprintf(STDERR_FILENO, "%s: ", PROGRAM_NAME);
		perror(NULL);
		return (false);
	}
	return (true);
}
