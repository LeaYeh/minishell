#include "executor.h"
#include "utils.h"
#include "clean.h"
#include "debug.h"
#include "signals.h"

void	handle_external_cmd(t_shell *shell, t_cmd_table *cmd_table)
{
	t_final_cmd_table	*final_cmd_table;

	final_cmd_table = shell->final_cmd_table;
	if (!handle_io_redirect(final_cmd_table, cmd_table->io_red_list))
		ft_clean_and_exit_shell(shell, GENERAL_ERROR, NULL);
	if (!redirect_io(shell) || \
		!check_executable(shell, final_cmd_table->exec_path))
		ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
	setup_signal(shell, SIGINT, SIG_DEFAULT);
	setup_signal(shell, SIGQUIT, SIG_DEFAULT);
	setup_signal(shell, SIGTERM, SIG_DEFAULT);
	execve(final_cmd_table->exec_path, final_cmd_table->simple_cmd,
		final_cmd_table->envp);
	ft_clean_and_exit_shell(shell, CMD_EXEC_FAILED, "execve failed");
}
