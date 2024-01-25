#include "executor.h"
#include "utils.h"
#include "clean.h"
#include "debug.h"

void	bind_io_and_exec_external(
	t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	if (!redirect_io(shell, final_cmd_table))
	{
		free_final_cmd_table(&final_cmd_table);
		ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
	}
	execve(final_cmd_table->exec_path, final_cmd_table->simple_cmd,
		final_cmd_table->envp);
	free_final_cmd_table(&final_cmd_table);
	ft_clean_and_exit_shell(shell, CMD_EXEC_FAILED, "execve failed");
}

void	handle_external_cmd(t_shell *shell, t_cmd_table *cmd_table)
{
	t_final_cmd_table	*final_cmd_table;

	final_cmd_table = get_final_cmd_table(shell, cmd_table);
	if (!final_cmd_table)
		ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
	print_final_cmd_table(final_cmd_table);
	if (!redirect_io(shell, final_cmd_table) || \
		!check_executable(shell, final_cmd_table->exec_path))
	{
		free_final_cmd_table(&final_cmd_table);
		ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
	}
	execve(final_cmd_table->exec_path, final_cmd_table->simple_cmd,
		final_cmd_table->envp);
	free_final_cmd_table(&final_cmd_table);
	ft_clean_and_exit_shell(shell, CMD_EXEC_FAILED, "execve failed");
}
