/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:06:39 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 17:36:42 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "executor.h"
#include "signals.h"
#include "utils.h"

bool	init_shell(t_sh *shell)
{
	shell->is_interactive = isatty(STDIN_FILENO);
	shell->pid = getpid_from_proc();
	shell->subshell_pid = -1;
	shell->subshell_level = 0;
	shell->signal_record = 0;
	init_pipe(&shell->old_pipe);
	init_pipe(&shell->new_pipe);
	shell->exit_code = EXIT_SUCCESS;
	shell->child_pid_list = NULL;
	shell->env_list = NULL;
	shell->token_list = NULL;
	shell->final_cmd_table = NULL;
	shell->cmd_table_list = NULL;
	shell->input_line = NULL;
	if (!setup_env_list(shell))
		return (false);
	handle_signal_std(0, NULL, shell);
	handle_signal_record(0, NULL, shell);
	setup_signal(shell, SIGINT, SIG_STANDARD);
	setup_signal(shell, SIGABRT, SIG_STANDARD);
	setup_signal(shell, SIGTERM, SIG_STANDARD);
	setup_signal(shell, SIGQUIT, SIG_IGNORE);
	return (true);
}
