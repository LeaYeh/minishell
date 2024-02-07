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

static bool	extract_string(char **res, char *str, char *delim)
{
	char	*tmp;

	tmp = ft_strtok(str, delim);
	if (tmp)
	{
		*res = ft_strdup(tmp);
		if (!*res)
			return (false);
	}
	else
		*res = NULL;
	return (true);
}

// If no OLDPWD key exists, create one with no VALUE
bool	add_default_oldpwd_env_node(t_list **env_list)
{
	char	*key;
	char	*value;

	key = ft_strdup("OLDPWD");
	if (!key)
		return (false);
	value = NULL;
	if (!append_env_node(env_list, key, value, X_EXPORT_YES))
		return (free(key), false);
	return (true);
}

bool	add_default_pwd_env_node(t_list **env_list)
{
	char	*key;
	char	*value;

	key = ft_strdup("PWD");
	if (!key)
		return (false);
	value = getcwd(NULL, 0);
	if (!value)
		return (free(key), false);
	if (!append_env_node(env_list, key, value, X_EXPORT_YES))
		return (free(key), free(value), false);
	return (true);
}

bool	setup_default_env_list(t_shell *shell, char **env)
{
	if (!is_key_in_env(env, "OLDPWD") && \
		!add_default_oldpwd_env_node(&shell->env_list))
		return (false);
	if (!is_key_in_env(env, "PWD") && \
		!add_default_pwd_env_node(&shell->env_list))
		return (false);
	return (true);
}

bool	process_env_str_to_env_list(char *env_str, t_list **env_list)
{
	char	*key;
	char	*value;

	if (!extract_string(&key, env_str, "="))
		return (false);
	if (ft_strcmp(key, "PWD") == 0)
	{
		value = getcwd(NULL, 0);
		if (!value)
			return (free(key), false);
	}
	else if (!extract_string(&value, NULL, ""))
		return (free(key), false);
	if (ft_strcmp(key, "OLDPWD") == 0 && value && !is_dir(value))
	{
		free(key);
		free(value);
	}
	else if (!append_env_node(env_list, key, value, X_EXPORT_YES))
		return (free(key), free(value), false);
	return (true);
}

// PWD should always be set by current shell
// If OLDPWD exists and has value, if value is not a real directory,
// delete OLDPWD entirely (permissions don't matter)
bool	setup_env_list(t_shell *shell, char **env)
{
	int		i;

	if (!setup_default_env_list(shell, env))
		return (false);
	if (!env)
		return (true);
	i = 0;
	while (env[i])
	{
		if (!process_env_str_to_env_list(env[i], &shell->env_list))
			return (false);
		i++;
	}
	return (true);
}

bool	init_shell(t_shell *shell, char **env)
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
	if (!setup_env_list(shell, env))
		return (false);
	handle_signal_std(0, NULL, shell);
	handle_signal_heredoc(0, NULL, shell);
	setup_signal(shell, SIGINT, SIG_STD);
	setup_signal(shell, SIGABRT, SIG_STD);
	setup_signal(shell, SIGTERM, SIG_STD);
	setup_signal(shell, SIGQUIT, SIG_IGNORE);
	return (true);
}
