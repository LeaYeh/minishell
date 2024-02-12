#ifndef INIT_H
# define INIT_H

# include "defines.h"

bool	init_shell(t_shell *shell);
bool	setup_env_list(t_shell *shell);
bool	setup_default_env_list(t_shell *shell);
bool	check_special_env_vars(t_list **tmp_list);

#endif
