/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:10 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 17:40:11 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include "clean.h"

void	handle_exit(t_shell *shell, int args_error)
{
	if (shell->subshell_level == 0 && !TEST_MODE)
		ft_dprintf(STDERR_FILENO, EXIT_MSG);
	if (args_error == EX_TOO_MANY_ARGS)
	{
		ft_dprintf(2, ERROR_EXIT_TOO_MANY_ARGS, PROGRAM_NAME, "exit");
		if (shell->subshell_level == 0)
			return ;
	}
	else if (args_error == EX_NOT_NUMERIC)
		ft_dprintf(2, ERROR_EXIT_NUMERIC_ARG,
			PROGRAM_NAME, "exit", shell->final_cmd_table->simple_cmd[1]);
	clean_and_exit_shell(shell, shell->exit_code, NULL);
}

void	exec_exit(t_shell *shell, char *args[])
{
	int	args_error;

	args_error = get_args_error(args);
	if (args_error == EX_NORM_ARGS)
		shell->exit_code = (ft_atol(args[1])) % 256;
	else if (args_error != EX_NO_ARGS)
		shell->exit_code = args_error;
	handle_exit(shell, args_error);
}
