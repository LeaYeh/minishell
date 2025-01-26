/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:06:39 by lyeh              #+#    #+#             */
/*   Updated: 2025/01/26 21:52:59 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "executor.h"
#include "signals.h"
#include "utils.h"

bool	init_shell(t_sh *shell)
{
	ft_bzero(shell, sizeof(t_sh));
	shell->is_interactive = isatty(STDIN_FILENO);
	rl_outstream = stderr;
	shell->pid = getpid_from_proc();
	shell->subshell_pid = -1;
	init_pipe(&shell->old_pipe);
	init_pipe(&shell->new_pipe);
	shell->exit_code = EXIT_SUCCESS;
	if (!setup_env_list(shell))
		return (false);
	handle_signal_std(0, NULL, shell);
	handle_signal_record(0, NULL, shell);
	setup_signal(SIGINT, SIG_STANDARD);
	setup_signal(SIGTERM, SIG_STANDARD);
	setup_signal(SIGUSR1, SIG_STANDARD);
	setup_signal(SIGQUIT, SIG_IGNORE);
	setup_signal(SIGPIPE, SIG_STANDARD);
	return (true);
}
