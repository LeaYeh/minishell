/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:10:43 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/10 18:35:36 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "utils.h"

void	handle_builtin(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	shell->subshell_pid = 0;
	shell->exit_code = GENERAL_ERROR;
	if (!cmd_table->cmd_name)
		return ;
	if (ft_strcmp(cmd_table->cmd_name, "env") == 0)
		shell->exit_code = ft_exec_env(shell);
	else if (ft_strcmp(cmd_table->cmd_name, "unset") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(cmd_table->cmd_name, "echo") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(cmd_table->cmd_name, "pwd") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(cmd_table->cmd_name, "cd") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(cmd_table->cmd_name, "export") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(cmd_table->cmd_name, "exit") == 0)
		shell->exit_code = 123;
	*cmd_table_node = (*cmd_table_node)->next;
}
