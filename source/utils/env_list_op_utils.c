/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_op_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:31:17 by ldulling          #+#    #+#             */
/*   Updated: 2024/02/18 00:15:53 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "clean.h"

bool	append_env_node(
	t_list **env_list, char *key, char *value, t_export export)
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

bool	process_str_to_env_list(char *str, t_list **env_list, t_export export)
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
