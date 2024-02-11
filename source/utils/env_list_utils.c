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

bool	is_exported_env_node(t_list *env_list, char *key)
{
	t_env	*env_node;

	while (env_list)
	{
		env_node = env_list->content;
		if (ft_strcmp(env_node->key, key) == 0 && \
			env_node->export == X_EXPORT_YES)
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
			return (env_node->value);
		env_list = env_list->next;
	}
	return (NULL);
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
