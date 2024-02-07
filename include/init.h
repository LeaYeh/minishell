#ifndef INIT_H
# define INIT_H

# include "defines.h"

bool	init_shell(t_shell *shell, char **env);
bool	setup_env_list(t_shell *shell, char **env);
bool	setup_default_env_list(t_shell *shell, char **env);

#endif
