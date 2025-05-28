/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:22:50 by lyeh              #+#    #+#             */
/*   Updated: 2025/05/28 23:53:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "utils.h"

static bool	check_special_env_vars(t_list **env_list, t_list **tail);
static bool	handle_pwd(t_env *env_node);
static bool	handle_oldpwd(t_env *env_node, t_list **env_list, t_list **tail);

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
		ft_lstadd_back_tail(&shell->env_list, &tail, new_node);
		if (!check_special_env_vars(&shell->env_list, &tail))
			return (false);
		i++;
	}
	return (true);
}

/**
 * Special env variables get set on startup, under certain circumstances.
 */
static bool	check_special_env_vars(t_list **env_list, t_list **tail)
{
	t_env	*env_node;

	env_node = (*tail)->content;
	if (ft_strcmp(env_node->key, "PWD") == 0)
		return (handle_pwd(env_node));
	if (ft_strcmp(env_node->key, "OLDPWD") == 0)
		return (handle_oldpwd(env_node, env_list, tail));
	return (true);
}

/**
 * PWD should always be set by the current shell, unless getcwd fails.
 */
static bool	handle_pwd(t_env *env_node)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		if (errno == ENOMEM)
			return (false);
		print_error(
			"%s: %s: %s\n", PROGRAM_NAME, "getcwd", strerror(errno));
		return (true);
	}
	free(env_node->value);
	env_node->value = pwd;
	return (true);
}

/**
 * If OLDPWD exists and its value is not a real directory, delete OLDPWD 
 * entirely (permissions don't matter).
 */
static bool	handle_oldpwd(t_env *env_node, t_list **env_list, t_list **tail)
{
	if (env_node->value && !is_dir(env_node->value))
	{
		ft_lstdrop_node(env_list, tail, (void *)free_env_node);
		*tail = ft_lstlast(*env_list);
	}
	return (true);
}
