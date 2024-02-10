#include "utils.h"

// If no OLDPWD key exists, create one with no VALUE
bool	add_default_oldpwd_env_node(t_list **env_list)
{
	char	*key;
	char	*value;

	key = ft_strdup("OLDPWD");
	if (!key)
		return (false);
	value = NULL;
	if (!append_env_node(env_list, key, value, V_EXPORT_YES))
		return (free(key), false);
	return (true);
}

bool	add_default_pwd_env_node(t_list **env_list)
{
	char	*key;
	char	*value;

	key = ft_strdup("PWD");
	if (!key)
		return (false);
	value = getcwd(NULL, 0);
	if (!value)
		return (free(key), false);
	if (!append_env_node(env_list, key, value, V_EXPORT_YES))
		return (free(key), free(value), false);
	return (true);
}

bool	setup_default_env_list(t_shell *shell)
{
	extern char	**environ;

	if (!is_key_in_env(environ, "OLDPWD") && \
		!add_default_oldpwd_env_node(&shell->env_list))
		return (false);
	if (!is_key_in_env(environ, "PWD") && \
		!add_default_pwd_env_node(&shell->env_list))
		return (false);
	return (true);
}
