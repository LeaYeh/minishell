#include "signals.h"

void	handle_signal_std(int signo, siginfo_t *info, void *context)
{
	static t_shell	*shell;

	(void)info;
	if (!shell)
	{
		shell = context;
		return ;
	}
	// printf("handle_signal_std state: %d, pid: %d\n", signo, getpid());
	shell->exit_code = TERM_BY_SIGNAL + signo;
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGTERM)
		ft_clean_and_exit_shell(shell, TERM_BY_SIGNAL + SIGTERM, NULL);
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
	if (state == SIG_STD)
		sa.sa_sigaction = handle_signal_std;
	else if (state == SIG_HEREDOC)
		sa.sa_sigaction = handle_signal_heredoc;
	else if (state == SIG_IGNORE)
		sa.sa_handler = SIG_IGN;
	else if (state == SIG_DEFAULT)
		sa.sa_handler = SIG_DFL;
	if (sigaction(signo, &sa, NULL) != 0)
		perror("The signal is not supported");
}
