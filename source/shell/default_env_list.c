/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:22:47 by lyeh              #+#    #+#             */
/*   Updated: 2025/05/28 17:32:17 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static bool	add_default_oldpwd_env_node(t_list **env_list);
static bool	add_default_pwd_env_node(t_list **env_list);

bool	setup_default_env_list(t_sh *shell)
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

/**
 * If no OLDPWD key exists, create one with no VALUE
 */
static bool	add_default_oldpwd_env_node(t_list **env_list)
{
	char	*key;
	char	*value;

	key = ft_strdup("OLDPWD");
	if (!key)
		return (false);
	value = NULL;
	if (!append_env_node(env_list, &key, &value, EXPORT_YES))
		return (free(key), false);
	return (true);
}

static bool	add_default_pwd_env_node(t_list **env_list)
{
	char	*key;
	char	*value;

	key = ft_strdup("PWD");
	if (!key)
		return (false);
	value = getcwd(NULL, 0);
	if (!value)
	{
		free(key);
		if (errno == ENOMEM)
			return (false);
		print_error("%s: %s: %s\n", PROGRAM_NAME, "getcwd", strerror(errno));
		return (true);
	}
	if (!append_env_node(env_list, &key, &value, EXPORT_YES))
		return (free(key), free(value), false);
	return (true);
}
