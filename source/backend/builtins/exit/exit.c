/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:10 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/28 22:38:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "clean.h"

static void	handle_exit(t_sh *shell, t_exit_err args_error);

void	exec_exit(t_sh *shell, char *args[])
{
	t_exit_err	args_error;

	args_error = get_args_error(args);
	if (args_error == EX_NORM_ARGS)
		shell->exit_code = ft_atol(args[1]);
	else if (args_error != EX_NO_ARGS)
		shell->exit_code = args_error;
	handle_exit(shell, args_error);
}

static void	handle_exit(t_sh *shell, t_exit_err args_error)
{
	if (shell->subshell_level == 0 && shell->is_interactive)
		ft_dprintf(STDERR_FILENO, EXIT_MSG);
	if (args_error == EX_TOO_MANY_ARGS)
	{
		ft_dprintf(STDERR_FILENO, ERROR_EXIT_TOO_MANY_ARGS,
			PROGRAM_NAME, "exit");
		if (shell->subshell_level == 0)
			return ;
	}
	else if (args_error == EX_NOT_NUMERIC)
		ft_dprintf(STDERR_FILENO, ERROR_EXIT_NUMERIC_ARG,
			PROGRAM_NAME, "exit", shell->final_cmd_table->simple_cmd[1]);
	clean_and_exit_shell(shell, shell->exit_code, NULL);
}
