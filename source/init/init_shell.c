/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:06:39 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/20 12:44:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "utils.h"
#include "signals.h"

bool	init_shell(t_shell *shell)
{
	shell->pid = getpid();
	shell->subshell_pid = -1;
	shell->subshell_level = 0;
	init_pipe(&shell->old_pipe);
	init_pipe(&shell->new_pipe);
	shell->exit_code = EXIT_SUCCESS;
	shell->child_pid_list = NULL;
	shell->env_list = NULL;
	shell->token_list = NULL;
	shell->final_cmd_table = NULL;
	// shell->ast = NULL;
	shell->cmd_table_list = NULL;
	shell->input_line = NULL;
	if (!setup_env_list(shell))
		return (false);
	handle_signal_std(0, NULL, shell);
	handle_signal_heredoc(0, NULL, shell);
	setup_signal(shell, SIGINT, SIG_STANDARD);
	setup_signal(shell, SIGABRT, SIG_STANDARD);
	setup_signal(shell, SIGTERM, SIG_STANDARD);
	setup_signal(shell, SIGQUIT, SIG_IGNORE);
	return (true);
}
