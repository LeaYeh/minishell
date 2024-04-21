/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_broadcaster.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:41 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 17:48:59 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "utils.h"

static void	signal_to_all_subprocess(t_sh *shell, int signo);

void	raise_error_and_escape(t_sh *shell, char *msg)
{
	if (msg)
		printf(STY_RED"%s: error: %s\n"STY_RES, PROGRAM_NAME, msg);
	kill(-shell->pid, SIGABRT);
}

void	raise_error_to_all_subprocess(t_sh *shell, int exit_code, char *msg)
{
	shell->exit_code = exit_code;
	if (msg)
		printf(STY_RED"%s: error: %s\n"STY_RES, PROGRAM_NAME, msg);
	setup_signal(shell, SIGINT, SIG_STANDARD);
	setup_signal(shell, SIGABRT, SIG_STANDARD);
	setup_signal(shell, SIGQUIT, SIG_IGNORE);
	kill(-shell->pid, SIGTERM);
}

void	raise_error_to_own_subprocess(t_sh *shell, int exit_code, char *msg)
{
	shell->exit_code = exit_code;
	if (msg)
		printf(STY_RED"%s: error: %s\n"STY_RES, PROGRAM_NAME, msg);
	setup_signal(shell, SIGINT, SIG_STANDARD);
	setup_signal(shell, SIGABRT, SIG_STANDARD);
	setup_signal(shell, SIGTERM, SIG_STANDARD);
	setup_signal(shell, SIGQUIT, SIG_IGNORE);
	signal_to_all_subprocess(shell, SIGTERM);
	kill(getpid_from_proc(), SIGTERM);
}

static void	signal_to_all_subprocess(t_sh *shell, int signo)
{
	pid_t	pid;
	pid_t	child_pid;
	t_list	*node;

	pid = getpid_from_proc();
	node = shell->child_pid_list;
	while (node)
	{
		child_pid = (pid_t)(long)node->content;
		if (child_pid == pid)
			break ;
		kill(child_pid, signo);
		node = node->next;
	}
}
