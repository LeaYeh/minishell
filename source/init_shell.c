/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:06:39 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/20 12:44:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean.h"
#include "utils.h"
#include "signals.h"

bool	ft_append_env(t_list **env_list, char *key, char *value)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (!env_node)
		return (false);
	env_node->key = key;
	env_node->value = value;
	if (!ft_lstnew_back(env_list, env_node))
		return (free(env_node), false);
	return (true);
}

// TODO: Not implemented yet
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
		if (!extract_string(&value, NULL, ""))
			break ;
		if (!append_env_node(&shell->env_list, key, value, X_EXPORT_YES))
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
	shell->pid = getpid();
	shell->subshell_pid = -1;
	shell->subshell_level = 0;
	init_pipe(&shell->old_pipe);
	init_pipe(&shell->new_pipe);
	shell->exit_status = 0;
	shell->exit_code = EXIT_SUCCESS;
	shell->child_pid_list = NULL;
	shell->env_list = NULL;
	shell->token_list = NULL;
	shell->final_cmd_table = NULL;
	// shell->ast = NULL;
	shell->cmd_table_list = NULL;
	shell->input_line = NULL;
	if (!ft_setup_env(shell, env))
		return (false);
	handle_signal_std(0, NULL, shell);
	handle_signal_heredoc(0, NULL, shell);
	setup_signal(shell, SIGINT, SIG_STD);
	setup_signal(shell, SIGABRT, SIG_STD);
	setup_signal(shell, SIGTERM, SIG_STD);
	setup_signal(shell, SIGQUIT, SIG_IGNORE);
	return (true);
}
