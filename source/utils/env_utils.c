#include "defines.h"

bool	extract_env_key(char **res, const char *str)
{
	char	*equal_sign;
	int		res_len;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
		res_len = equal_sign - str;
	else
		res_len = ft_strlen(str);
	*res = ft_substr(str, 0, res_len);
	if (!*res)
		return (false);
	return (true);
}

bool	extract_env_value(char **res, const char *str)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		*res = NULL;
	else
	{
		*res = ft_strdup(equal_sign + 1);
		if (!*res)
			return (false);
	}
	return (true);
}

static char	*get_value_with_key(char *str, char *key)
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

char	*get_value_from_env(char *env[], char *key)
{
	int		i;
	char	*value;

	if (!env || !key)
		return (NULL);
	value = NULL;
	i = 0;
	while (env[i])
	{
		value = get_value_with_key(env[i], key);
		if (value)
			break ;
		i++;
	}
	return (value);
}

bool	is_key_in_env(char *env[], char *key)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return (false);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && \
			(env[i][key_len] == '=' || env[i][key_len] == '\0'))
			return (true);
		i++;
	}
	return (false);
}

bool	replace_env_str(char *env[], const char *key, char *new_str)
{
	int		i;
	int		key_len;
	char	*tmp;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && \
			(env[i][key_len] == '=' || env[i][key_len] == '\0'))
		{
			tmp = ft_strdup(new_str);
			if (!tmp)
				return (false);
			free(env[i]);
			env[i] = tmp;
			return (true);
		}
		i++;
	}
	return (true);
}
