/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:46:19 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/19 10:27:36 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "clean.h"

void	handle_signal_std(int signo, siginfo_t *info, void *context)
{
	static t_shell	*shell;

	(void)info;
	if (!shell)
		return (shell = context, (void) NULL);
	shell->exit_code = TERM_BY_SIGNAL + signo;
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGABRT)
	{
		if (shell->subshell_level == 0)
			ft_clean_and_exit_shell(
				shell, shell->exit_code, "Clean up and abort the program");
		else
			ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
	}
	else if (signo == SIGTERM && shell->subshell_level != 0)
		ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
}

void	handle_signal_record(int signo, siginfo_t *info, void *context)
{
	static t_shell	*shell;

	(void)info;
	if (!shell)
	{
		shell = context;
		return ;
	}
	shell->signal_record = signo;
}

void	handle_signal_heredoc(int signo, siginfo_t *info, void *context)
{
	static t_shell	*shell;

	(void)info;
	if (!shell)
	{
		shell = context;
		return ;
	}
	shell->exit_code = TERM_BY_SIGNAL + signo;
	if (signo == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	setup_signal(t_shell *shell, int signo, t_state state)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		ft_clean_and_exit_shell(shell, PREPROCESS_ERROR, "sigemptyset failed");
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (state == SIG_DEFAULT)
		sa.sa_handler = SIG_DFL;
	else if (state == SIG_IGNORE)
		sa.sa_handler = SIG_IGN;
	else if (state == SIG_STANDARD)
		sa.sa_sigaction = handle_signal_std;
	else if (state == SIG_RECORD)
		sa.sa_sigaction = handle_signal_record;
	else if (state == SIG_HEREDOC)
		sa.sa_sigaction = handle_signal_heredoc;
	if (sigaction(signo, &sa, NULL) != 0)
		perror("The signal is not supported:");
}
