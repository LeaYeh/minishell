#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include "defines.h"
# include "clean.h"
// # include <termios.h>


void	handle_signal_std(int signo, siginfo_t *info, void *context);
void	handle_signal_heredoc(int signo, siginfo_t *info, void *context);
void	setup_signal(t_shell *shell, int signo, t_sig_state state);
void	handle_sigint_enf_of_pipeline(t_shell *shell);
void	raise_error_and_escape(t_shell *shell, char *msg);
void	raise_error_to_all_subprocess(t_shell *shell, int exit_code, char *msg);
void	raise_error_to_own_subprocess(t_shell *shell, int exit_code, char *msg);

#endif
