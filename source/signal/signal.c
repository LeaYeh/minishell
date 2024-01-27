#include "signals.h"

void	raise_internal_error(t_shell *shell, char *msg)
{
	if (msg)
		printf(STY_RED"Crash error: %s\n"STY_RES, msg);
	kill(-shell->pid, SIGABRT);
	kill(shell->pid, SIGABRT);
}

void	handle_signal_subshell(int signo, siginfo_t *info, void *context)
{
	static t_shell	*shell;

	(void)info;
	if (!shell)
	{
		shell = context;
		return ;
	}
	shell->exit_code = TERM_BY_SIGNAL + signo;
	if (signo == SIGABRT)
		ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
}

void	handle_signal_std(int signo, siginfo_t *info, void *context)
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
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGABRT)
		ft_clean_and_exit_shell(
			shell, shell->exit_code, "Clean up and abort the program");
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
	if (state == SIG_HEREDOC)
		sa.sa_sigaction = handle_signal_heredoc;
	else if (state == SIG_STD)
		sa.sa_sigaction = handle_signal_std;
	else if (state == SIG_SUBSHELL)
		sa.sa_sigaction = handle_signal_subshell;
	else if (state == SIG_DEFAULT)
		sa.sa_handler = SIG_DFL;
	else if (state == SIG_IGNORE)
		sa.sa_handler = SIG_IGN;
	if (sigaction(signo, &sa, NULL) != 0)
		perror("The signal is not supported");
}
