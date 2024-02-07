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
#include "minishell.h"

bool	update_pwd_env(t_list **env_list, char *new_pwd)
{
	char	*old_pwd;

	old_pwd = replace_env_value(*env_list, "PWD", new_pwd);
	if (old_pwd)
	{
		if (!handle_existing_pwd(env_list, old_pwd))
			return (free(old_pwd), false);
	}
	else
		if (!handle_non_existing_pwd(env_list, new_pwd))
			return (false);
	return (true);
}

bool	handle_existing_pwd(t_list **env_list, char *old_pwd)
{
	char	*key;
	char	*tmp;

	tmp = replace_env_value(*env_list, "OLDPWD", old_pwd);
	if (tmp)
		free(tmp);
	else
	{
		key = ft_strdup("OLDPWD");
		if (!key)
			return (false);
		if (!ft_append_env(env_list, key, old_pwd, X_EXPORT_NO))
			return (free(key), false);
	}
	return (true);
}

bool	handle_non_existing_pwd(t_list **env_list, char *new_pwd)
{
	char	*key;

	key = ft_strdup("PWD");
	if (!key)
		return (false);
	if (!ft_append_env(env_list, key, new_pwd, X_EXPORT_NO))
		return (free(key), false);
	remove_env_node(env_list, "OLDPWD", NULL);
	return (true);
}
