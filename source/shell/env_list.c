/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:22:50 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 17:36:41 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "utils.h"

static bool	check_special_env_vars(t_list **env_list);

bool	setup_env_list(t_sh *shell)
{
	extern char	**environ;
	int			i;
	t_list		*tmp_list;

	if (!setup_default_env_list(shell))
		return (false);
	if (!environ)
		return (true);
	i = 0;
	while (environ[i])
	{
		tmp_list = NULL;
		if (!process_str_to_env_list(environ[i], &tmp_list, EXPORT_YES))
			return (false);
		if (!check_special_env_vars(&tmp_list))
			return (ft_lstclear(&tmp_list, free), false);
		ft_lstadd_back(&shell->env_list, tmp_list);
		i++;
	}
	return (true);
}

/**
 * PWD should always be set by current shell.
 * If OLDPWD exists and its value is not a real directory,
 * delete OLDPWD entirely (permissions don't matter).
 */
static bool	check_special_env_vars(t_list **env_list)
{
	t_env	*env_node;

	env_node = (*env_list)->content;
	if (ft_strcmp(env_node->key, "PWD") == 0)
	{
		free(env_node->value);
		env_node->value = getcwd(NULL, 0);
		if (!env_node->value)
			return (false);
	}
	else if (ft_strcmp(env_node->key, "OLDPWD") == 0 && \
			env_node->value && !is_dir(env_node->value))
		ft_lstclear(env_list, free);
	return (true);
}
