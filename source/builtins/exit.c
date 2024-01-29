#include "builtins.h"
#include "utils.h"
#include "clean.h"

void	handle_exit(t_shell *shell, int args_error)
{
	if (shell->subshell_level == 0 && !DEBUG_MODE)
		printf(EXIT_STR "\n");
	if (args_error == TOO_MANY_ARGS)
	{
		ft_dprintf(2, ERROR_EXIT_TOO_MANY_ARGS, PROGRAM_NAME, "exit");
		if (shell->subshell_level == 0)
			return ;
	}
	else if (args_error == NOT_NUMERIC)
		ft_dprintf(2, ERROR_EXIT_NUMERIC_ARG,
			PROGRAM_NAME, "exit", shell->final_cmd_table->simple_cmd[1]);
	ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
}

void	exec_exit(t_shell *shell)
{
	t_final_cmd_table	*final_cmd_table;
	int					args_error;
	char				**args;

	final_cmd_table = shell->final_cmd_table;
	args = &final_cmd_table->simple_cmd[1];
	args_error = get_args_error(args);
	if (args_error == NO_ARGS)
		shell->exit_code = SUCCESS;
	else if (args_error == NORM_ARGS)
		shell->exit_code = (ft_atol(args[0])) % 256;
	else
		shell->exit_code = args_error;
	handle_exit(shell, args_error);
}
