#include "signals.h"

void	raise_error_and_escape(t_shell *shell, char *msg)
{
	if (msg)
		printf(STY_RED"%s: error: %s\n"STY_RES, PROGRAM_NAME, msg);
	kill(-shell->pid, SIGABRT);
}

void	raise_error_to_all_subprocess(t_shell *shell, int exit_code, char *msg)
{
	shell->exit_code = exit_code;
	if (msg)
		printf(STY_RED"%s: error: %s\n"STY_RES, PROGRAM_NAME, msg);
	setup_signal(shell, SIGINT, SIG_STANDARD);
	setup_signal(shell, SIGABRT, SIG_STANDARD);
	setup_signal(shell, SIGQUIT, SIG_IGNORE);
	kill(-shell->pid, SIGTERM);
}

void	signal_to_all_subprocess(t_shell *shell, int signo)
{
	pid_t	pid;
	pid_t	child_pid;
	t_list	*node;

	pid = getpid();
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

void	raise_error_to_own_subprocess(t_shell *shell, int exit_code, char *msg)
{
	// pid_t	pid;

	shell->exit_code = exit_code;
	if (msg)
		printf(STY_RED"%s: error: %s\n"STY_RES, PROGRAM_NAME, msg);
	setup_signal(shell, SIGINT, SIG_STANDARD);
	setup_signal(shell, SIGABRT, SIG_STANDARD);
	setup_signal(shell, SIGTERM, SIG_STANDARD);
	setup_signal(shell, SIGQUIT, SIG_IGNORE);
	signal_to_all_subprocess(shell, SIGTERM);
	kill(getpid(), SIGTERM);
}

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
