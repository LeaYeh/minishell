#include "builtins.h"
#include "utils.h"
#include "clean.h"

void	handle_too_many_args(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	if (shell->subshell_level == 0)
		printf("exit\n");
	ft_dprintf(2, ERROR_EXIT_TOO_MANY_ARGS, PROGRAM_NAME, "exit");
	if (shell->subshell_level != 0)
	{
		free_final_cmd_table(&final_cmd_table);
		ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
	}
}

void	handle_general_exit(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	if (shell->subshell_level == 0)
		printf("exit\n");
	if (shell->exit_code == NOT_NUMERIC)
		ft_dprintf(2, ERROR_EXIT_NUMERIC_ARG,
			PROGRAM_NAME, "exit", final_cmd_table->simple_cmd[1]);
	free_final_cmd_table(&final_cmd_table);
	ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
}

void	exec_exit(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	int		args_error;
	char	**args;

	args = &final_cmd_table->simple_cmd[1];
	args_error = get_args_error(args);
	if (args_error == NO_ARGS)
		shell->exit_code = SUCCESS;
	else if (args_error == NORM_ARGS)
		shell->exit_code = ((long long)ft_atof(args[0])) % 256;
	else
		shell->exit_code = args_error;
	if (args_error != TOO_MANY_ARGS)
		handle_general_exit(shell, final_cmd_table);
	else
		handle_too_many_args(shell, final_cmd_table);

}
