/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_status_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:16:14 by lyeh              #+#    #+#             */
/*   Updated: 2024/02/18 00:17:58 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

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
