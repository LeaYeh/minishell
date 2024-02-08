#include "init.h"
#include "utils.h"

static bool	extract_string(char **res, char *str, char *delim)
{
	char	*tmp;

	tmp = ft_strtok(str, delim);
	if (tmp)
	{
		*res = ft_strdup(tmp);
		if (!*res)
			return (false);
	}
	else
		*res = NULL;
	return (true);
}

/*
 * PWD should always be set by current shell.
 * If OLDPWD exists and has value, if value is not a real directory,
 * delete OLDPWD entirely (permissions don't matter).
 */
bool	process_env_str_to_env_list(char *env_str, t_list **env_list)
{
	char	*key;
	char	*value;

	if (!extract_string(&key, env_str, "="))
		return (false);
	if (ft_strcmp(key, "PWD") == 0)
	{
		value = getcwd(NULL, 0);
		if (!value)
			return (free(key), false);
	}
	else if (!extract_string(&value, NULL, ""))
		return (free(key), false);
	if (ft_strcmp(key, "OLDPWD") == 0 && value && !is_dir(value))
	{
		free(key);
		free(value);
	}
	else if (!append_env_node(env_list, key, value, X_EXPORT_YES))
		return (free(key), free(value), false);
	return (true);
}

bool	setup_env_list(t_shell *shell)
{
	extern char	**environ;
	int	i;

	if (!setup_default_env_list(shell))
		return (false);
	if (!environ)
		return (true);
	i = 0;
	while (environ[i])
	{
		if (!process_env_str_to_env_list(environ[i], &shell->env_list))
			return (false);
		i++;
	}
	return (true);
}
