#ifndef SIGNALS_H
# define SIGNALS_H

# include "defines.h"
# include "clean.h"
// # include <termios.h>


void	handle_signal_std(int signo, siginfo_t *info, void *context);
void	handle_signal_heredoc(int signo, siginfo_t *info, void *context);
void	setup_signal(t_shell *shell, int signo, t_state state);
void	handle_sigint_enf_of_pipeline(t_shell *shell);

#endif
