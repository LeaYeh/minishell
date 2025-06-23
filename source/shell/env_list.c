/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:22:50 by lyeh              #+#    #+#             */
/*   Updated: 2025/06/23 10:24:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "utils.h"

static bool	check_special_env_vars(t_list **env_node);
static bool	handle_pwd(t_env *env_entry);
static bool	handle_oldpwd(t_list **env_node);

bool	setup_env_list(t_sh *shell)
{
	extern char	**environ;
	int			i;
	t_list		*new_node;
	t_list		*tail;

	if (!setup_default_env_list(shell))
		return (false);
	if (!environ)
		return (true);
	tail = ft_lstlast(shell->env_list);
	i = 0;
	while (environ[i])
	{
		new_node = NULL;
		if (!process_str_to_env_list(environ[i], &new_node, EXPORT_YES))
			return (false);
		if (!check_special_env_vars(&new_node))
			return (ft_lstclear(&new_node, (void *)free_env_node), false);
		ft_lstadd_back_tail(&shell->env_list, &tail, new_node);
		i++;
	}
	return (true);
}

/**
 * Special env variables get set on startup, under certain circumstances.
 */
static bool	check_special_env_vars(t_list **env_node)
{
	t_env	*env_entry;

	env_entry = (*env_node)->content;
	if (ft_strcmp(env_entry->key, "PWD") == 0)
		return (handle_pwd(env_entry));
	if (ft_strcmp(env_entry->key, "OLDPWD") == 0)
		return (handle_oldpwd(env_node));
	return (true);
}

/**
 * PWD should always be set by the current shell, unless getcwd fails.
 */
static bool	handle_pwd(t_env *env_entry)
{
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (errno == ENOMEM)
			return (false);
		print_error(
			"%s: %s: %s\n", PROGRAM_NAME, "getcwd", strerror(errno));
		return (true);
	}
	free(env_entry->value);
	env_entry->value = cwd;
	return (true);
}

/**
 * If OLDPWD exists and its value is not a real directory, delete OLDPWD 
 * entirely (permissions don't matter).
 */
static bool	handle_oldpwd(t_list **env_node)
{
	t_env	*env_entry;

	env_entry = (*env_node)->content;
	if (env_entry->value && !is_dir(env_entry->value))
		ft_lstdrop_node(env_node, env_node, (void *)free_env_node);
	return (true);
}
