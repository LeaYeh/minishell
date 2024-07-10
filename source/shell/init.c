/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:06:39 by lyeh              #+#    #+#             */
/*   Updated: 2024/06/01 11:50:48 by ldulling         ###   ########.fr       */
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
	setup_signal(SIGINT, SIG_STANDARD);
	setup_signal(SIGTERM, SIG_STANDARD);
	setup_signal(SIGUSR1, SIG_STANDARD);
	setup_signal(SIGQUIT, SIG_IGNORE);
	return (true);
}
