/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:31:17 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/20 19:43:11 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean.h"
#include "utils.h"

t_env	*init_env_node(char *key, char *value, t_env_scope scope)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	env_node->key = key;
	env_node->value = value;
	env_node->scope = scope;
	return (env_node);
}

bool	append_env_node(
	t_list **env_list, char *key, char *value, t_env_scope scope)
{
	t_env	*env_node;

	env_node = init_env_node(key, value, scope);
	if (!env_node)
		return (false);
	if (!ft_lstnew_back(env_list, env_node))
		return (free(env_node), false);
	return (true);
}

bool	prepend_env_node(
	t_list **env_list, char *key, char *value, t_env_scope scope)
{
	t_env	*env_node;

	env_node = init_env_node(key, value, scope);
	if (!env_node)
		return (false);
	if (!ft_lstnew_front(env_list, env_node))
		return (free(env_node), false);
	return (true);
}

bool	append_str_to_env_list(t_list **env_list, char *str, t_env_scope scope)
{
	char	*key;
	char	*value;

	if (!extract_env_key(&key, str))
		return (false);
	if (!extract_env_value(&value, str))
		return (free(key), false);
	if (!append_env_node(env_list, key, value, scope))
		return (free(key), free(value), false);
	return (true);
}

bool	prepend_str_to_env_list(t_list **env_list, char *str, t_env_scope scope)
{
	char	*key;
	char	*value;

	if (!extract_env_key(&key, str))
		return (false);
	if (!extract_env_value(&value, str))
		return (free(key), false);
	if (!prepend_env_node(env_list, key, value, scope))
		return (free(key), free(value), false);
	return (true);
}

t_env	*dup_env_node(t_env *env_node)
{
	t_env	*new_env_node;

	new_env_node = (t_env *)malloc(sizeof(t_env));
	if (!new_env_node)
		return (NULL);
	new_env_node->value = NULL;
	new_env_node->key = ft_strdup(env_node->key);
	if (!new_env_node->key)
		return (free_env_node(new_env_node), NULL);
	if (env_node->value)
	{
		new_env_node->value = ft_strdup(env_node->value);
		if (!new_env_node->value)
			return (free_env_node(new_env_node), NULL);
	}
	else
		new_env_node->value = NULL;
	new_env_node->scope = env_node->scope;
	return (new_env_node);
}

t_env	*find_env_node(t_list *env_list, char *key, char *value)
{
	t_env	*env_node;

	while (env_list)
	{
		env_node = env_list->content;
		if (key && value)
		{
			if (env_node->value && ft_strcmp(env_node->key, key) == 0 && \
				ft_strcmp(env_node->value, value) == 0)
				return (env_node);
		}
		else if (key)
		{
			if (ft_strcmp(env_node->key, key) == 0)
				return (env_node);
		}
		else if (value)
			if (env_node->value && ft_strcmp(env_node->value, value) == 0)
				return (env_node);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*get_value_from_env_list(t_list *env_list, char *key)
{
	t_env	*env_node;

	while (env_list)
	{
		env_node = env_list->content;
		if (ft_strcmp(env_node->key, key) == 0)
			return (printf("env_node->scope: %d\n", env_node->scope), env_node->value);
		env_list = env_list->next;
	}
	return (NULL);
}

bool	is_exported_env_node(t_list *env_list, char *key)
{
	t_env	*env_node;

	while (env_list)
	{
		env_node = env_list->content;
		if (ft_strcmp(env_node->key, key) == 0 && \
			env_node->scope == ENV_EXPORT)
			return (true);
		env_list = env_list->next;
	}
	return (false);
}

bool	is_key_in_env_list(t_list *env_list, char *key)
{
	t_list	*cur;
	t_env	*env_node;

	if (!env_list || !key)
		return (false);
	cur = env_list;
	while (cur)
	{
		env_node = (t_env *)cur->content;
		if (ft_strcmp(env_node->key, key) == 0)
			return (true);
		cur = cur->next;
	}
	return (false);
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
