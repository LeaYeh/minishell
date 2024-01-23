/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:02:15 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/05 16:25:40 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "executor.h"

void	free_env_node(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

void	ft_clean_shell(t_shell *shell)
{
	ft_lstclear(&shell->env_list, (void *)free_env_node);
	ft_lstclear(&shell->token_list, (void *)free_token_node);
	ft_lstclear_d(&shell->cmd_table_list, (void *)free_cmd_table);
	// free_ast_node(shell->ast);
	ft_free_and_null((void **)&shell->input_line);
}

void	reset_submodule_variable(t_shell *shell)
{
	shell->subshell_level = 0;
	ft_lstclear(&shell->token_list, (void *)free_token_node);
	ft_lstclear_d(&shell->cmd_table_list, (void *)free_cmd_table);
	ft_free_and_null((void **)&shell->input_line);
}

void	ft_clean_and_exit_shell(t_shell *shell, int exit_code, char *msg)
{
	if (msg)
		ft_dprintf(STDERR_FILENO, STY_YEL "%s\n" STY_RES, msg);
	ft_clean_shell(shell);
	safe_close_all_pipes(shell);
	exit(exit_code);
}
