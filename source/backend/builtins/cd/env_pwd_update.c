/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:56:50 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/26 14:57:15 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "utils.h"

static bool	handle_existing_pwd(t_list **env_list, char *prev_pwd);
static bool	handle_non_existing_pwd(t_list **env_list, char *new_pwd);

bool	update_pwd_env(t_list **env_list, char *new_pwd)
{
	char	*prev_pwd;

	if (replace_env_value(*env_list, "PWD", new_pwd, &prev_pwd))
	{
		if (!handle_existing_pwd(env_list, prev_pwd))
			return (free(prev_pwd), false);
	}
	else
		if (!handle_non_existing_pwd(env_list, new_pwd))
			return (false);
	return (true);
}

static bool	handle_existing_pwd(t_list **env_list, char *prev_pwd)
{
	char	*key;
	char	*prev_oldpwd;

	if (replace_env_value(*env_list, "OLDPWD", prev_pwd, &prev_oldpwd))
		free(prev_oldpwd);
	else
	{
		key = ft_strdup("OLDPWD");
		if (!key)
			return (false);
		if (!append_env_node(env_list, key, prev_pwd, EXPORT_NO))
			return (free(key), false);
	}
	return (true);
}

static bool	handle_non_existing_pwd(t_list **env_list, char *new_pwd)
{
	char	*key;

	key = ft_strdup("PWD");
	if (!key)
		return (false);
	if (!append_env_node(env_list, key, new_pwd, EXPORT_NO))
		return (free(key), false);
	remove_env_node(env_list, "OLDPWD", NULL);
	return (true);
}
