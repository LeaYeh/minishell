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

#include "cd.h"
#include "clean.h"
#include "minishell.h"

t_env	*find_env_node(t_list *env_list, char *key, char *value)
{
	t_env	*env_node;

	while (env_list)
	{
		env_node = env_list->content;
		if (key && value)
		{
			if (ft_strcmp(env_node->key, key) == 0 && \
				ft_strcmp(env_node->value, value) == 0)
				return (env_node);
		}
		else if (key)
		{
			if (ft_strcmp(env_node->key, key) == 0)
				return (env_node);
		}
		else if (value)
			if (ft_strcmp(env_node->value, value) == 0)
				return (env_node);
		env_list = env_list->next;
	}
	return (NULL);
}

// TODO: Almost the same function as get_replacement() from expander and get_value_from_env() from executor_utils
char	*get_value_from_env_list(t_list *env_list, char *key)
{
	t_env	*env_node;
	char	*value;

	value = NULL;
	while (env_list)
	{
		env_node = env_list->content;
		if (ft_strcmp(env_node->key, key) == 0)
		{
			value = env_node->value;
			break ;
		}
		env_list = env_list->next;
	}
	return (value);
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

char	*replace_env_value(t_list *env_list, char *key, char *value)
{
	t_env	*env_node;
	char	*old_value;

	env_node = find_env_node(env_list, key, NULL);
	if (!env_node)
		return (NULL);
	old_value = env_node->value;
	env_node->value = value;
	return (old_value);
}
