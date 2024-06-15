/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_operation_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:31:17 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/21 17:50:04 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "clean.h"

bool	append_env_node(
			t_list **env_list, char *key, char *value, t_expt export)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (!env_node)
		return (false);
	env_node->key = key;
	env_node->value = value;
	env_node->export = export;
	if (!ft_lstnew_back(env_list, env_node))
		return (free(env_node), false);
	return (true);
}

void	free_env_node(t_env *env)
{
	if (!env)
		return ;
	ft_free_and_null((void **)&env->key);
	ft_free_and_null((void **)&env->value);
	free(env);
}

bool	process_str_to_env_list(
			char *str, t_list **env_list, t_expt export)
{
	char	*key;
	char	*value;

	if (!extract_env_key(&key, str))
		return (false);
	if (!extract_env_value(&value, str))
		return (free(key), false);
	if (!append_env_node(env_list, key, value, export))
		return (free(key), free(value), false);
	return (true);
}

void	remove_env_node(t_list **env_list, char *key, char *value)
{
	t_list	*cur;
	t_env	*env_node;

	cur = *env_list;
	env_node = find_env_node(cur, key, value);
	while (env_node)
	{
		while (cur && cur->content != env_node)
			cur = cur->next;
		ft_lstdrop_node(env_list, &cur, (void *)free_env_node);
		env_node = find_env_node(cur, key, value);
	}
}

bool	replace_env_value(
			t_list *env_list, char *key, char *value, char **old_value)
{
	t_env	*env_node;

	env_node = find_env_node(env_list, key, NULL);
	if (!env_node)
		return (*old_value = NULL, false);
	*old_value = env_node->value;
	env_node->value = value;
	return (true);
}
