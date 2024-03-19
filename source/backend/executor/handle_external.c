#include "executor.h"
#include "utils.h"
#include "clean.h"
#include "debug.h"
#include "signals.h"

static bool	check_execfile_exist(char *exec_path, char *cmd_name);
static void	handle_exec_error(t_shell *shell, char *exec_path);

void	handle_external_cmd(t_shell *shell, t_cmd_table *cmd_table)
{
	t_final_cmd_table	*final_cmd_table;
	int					ret;

	final_cmd_table = shell->final_cmd_table;
	ret = handle_io_redirect(shell,
			&final_cmd_table->read_fd,
			&final_cmd_table->write_fd, cmd_table->io_red_list);
	if (ret == MALLOC_ERROR)
		raise_error_to_own_subprocess(shell, MALLOC_ERROR, "malloc failed");
	if (ret != SUCCESS)
		ft_clean_and_exit_shell(shell, GENERAL_ERROR, NULL);
	if (!shell->final_cmd_table->simple_cmd[0])
		ft_clean_and_exit_shell(shell, SUCCESS, NULL);
	if (!check_execfile_exist(final_cmd_table->exec_path,
			final_cmd_table->simple_cmd[0]))
		ft_clean_and_exit_shell(shell, CMD_NOT_FOUND, NULL);
	if (!redirect_scmd_io(shell, &final_cmd_table->read_fd,
			&final_cmd_table->write_fd))
		ft_clean_and_exit_shell(shell, GENERAL_ERROR, NULL);
	setup_signal(shell, SIGINT, SIG_DEFAULT);
	setup_signal(shell, SIGQUIT, SIG_DEFAULT);
	setup_signal(shell, SIGTERM, SIG_DEFAULT);
	setup_signal(shell, SIGABRT, SIG_DEFAULT);
	execve(final_cmd_table->exec_path, final_cmd_table->simple_cmd,
		final_cmd_table->env);
	handle_exec_error(shell, final_cmd_table->exec_path);
}

static bool	check_execfile_exist(char *exec_path, char *cmd_name)
{
	if (!exec_path)
		ft_dprintf(STDERR_FILENO, ERROR_CMD_NOT_FOUND, PROGRAM_NAME, cmd_name);
	else if (access(exec_path, F_OK) != 0 && errno != ENOTDIR)
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n",
			PROGRAM_NAME, exec_path, strerror(errno));
	else
		return (true);
	return (false);
}

static void	handle_exec_error(t_shell *shell, char *exec_path)
{
	int	error;

	error = errno;
	if (error == ENOEXEC)
		ft_dprintf(STDERR_FILENO, ERROR_CANNOT_EXEC_FILE,
			PROGRAM_NAME, exec_path, strerror(ENOEXEC));
	else if (is_dir(exec_path))
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n",
			PROGRAM_NAME, exec_path, strerror(EISDIR));
	else
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n",
			PROGRAM_NAME, exec_path, strerror(error));
	ft_clean_and_exit_shell(shell, CMD_EXEC_FAILED, NULL);
}
