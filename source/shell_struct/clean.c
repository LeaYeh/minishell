/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:02:15 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 17:36:38 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "executor.h"

void	free_env_node(t_env *env)
{
	if (!env)
		return ;
	ft_free_and_null((void **)&env->key);
	ft_free_and_null((void **)&env->value);
	ft_free_and_null((void **)&env);
}

void	clean_shell(t_shell *shell)
{
	ft_free_and_null((void **)&shell->input_line);
	ft_lstclear(&shell->child_pid_list, NULL);
	ft_lstclear(&shell->env_list, (void *)free_env_node);
	ft_lstclear(&shell->token_list, (void *)free_token_node);
	ft_lstclear_d(&shell->cmd_table_list, (void *)free_cmd_table);
	free_final_cmd_table(&shell->final_cmd_table);
	rl_clear_history();
}

void	reset_submodule_variable(t_shell *shell)
{
	shell->subshell_level = 0;
	shell->subshell_pid = -1;
	shell->signal_record = 0;
	ft_lstclear(&shell->child_pid_list, NULL);
	ft_lstclear(&shell->token_list, (void *)free_token_node);
	ft_lstclear_d(&shell->cmd_table_list, (void *)free_cmd_table);
	ft_free_and_null((void **)&shell->input_line);
	free_final_cmd_table(&shell->final_cmd_table);
}

void	clean_and_exit_shell(t_shell *shell, int exit_code, char *msg)
{
	if (msg)
		printf("%s\n", msg);
	clean_shell(shell);
	safe_close_all_pipes(shell);
	(void)get_next_line(-1);
	exit(exit_code);
}
