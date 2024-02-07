#include "defines.h"

static char	*get_value_from_str(char *str, char *key)
{
	int		key_len;
	char	*value;

	if (!str || !key)
		return (NULL);
	key_len = ft_strlen(key);
	if (ft_strncmp(str, key, key_len) == 0 && str[key_len] == '=')
	{
		value = str + key_len + 1;
		return (value);
	}
	return (NULL);
}

char	*get_value_from_env(char **envp, char *key)
{
	int		i;
	char	*value;

	if (!envp || !key)
		return (NULL);
	value = NULL;
	i = 0;
	while (envp[i])
	{
		value = get_value_from_str(envp[i], key);
		if (value)
			break ;
		i++;
	}
	return (value);
}

bool	is_key_in_env(char **envp, char *key)
{
	int	i;
	int	key_len;

	if (!envp || !key)
		return (false);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && \
			(envp[i][key_len] == '=' || envp[i][key_len] == '\0'))
			return (true);
		i++;
	}
	return (false);
}
