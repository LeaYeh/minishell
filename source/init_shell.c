/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:06:39 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/31 17:21:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean.h"

bool	ft_append_env(t_shell *shell, char *key, char *value)
{
	t_env	*env_node;
	t_list	*lst_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (!env_node)
		return (false);
	env_node->key = key;
	env_node->value = value;
	lst_node = ft_lstnew(env_node);
	if (!lst_node)
		return (false);
	ft_lstadd_back(&shell->env_list, lst_node);
	return (true);
}

bool	ft_setup_default_env(t_shell *shell)
{
	shell->env_list = NULL;
	return (true);
}

bool	extract_string(char **res, char *str, char *delim)
{
	char	*tmp;

	tmp = ft_strtok(str, delim);
	if (tmp)
		*res = ft_strdup(tmp);
	else
		*res = ft_strdup("");
	if (!*res)
		return (false);
	return (true);
}

bool	ft_setup_env(t_shell *shell, char **env)
{
	int		i;
	char	*key;
	char	*value;

	shell->env_list = NULL;
	key = NULL;
	value = NULL;
	i = 0;
	while (env[i])
	{
		if (!extract_string(&key, env[i], "="))
			break ;
		if (!extract_string(&value, NULL, "\n\0"))
			break ;
		if (!ft_append_env(shell, key, value))
			break ;
		i++;
	}
	if (env[i])
		return (ft_lstclear(&shell->env_list, (void *)free_env_node),
			free(key), free(value), false);
	return (true);
}

bool	ft_init_shell(t_shell *shell, char **env)
{
	shell->exit_code = EXIT_SUCCESS;
	shell->env_list = NULL;
	shell->token_list = NULL;
	// shell->ast = NULL;
	shell->cmd_table_list = NULL;
	shell->input_line = NULL;
	if (!env && !ft_setup_default_env(shell))
		return (false);
	else if (env && !ft_setup_env(shell, env))
		return (false);
	return (true);
}
