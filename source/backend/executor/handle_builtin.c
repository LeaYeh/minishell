/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:10:43 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/18 03:34:52 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "utils.h"

void	exec_builtin_cmd(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	if (ft_strcmp(final_cmd_table->simple_cmd[0], "env") == 0)
		shell->exit_code = ft_exec_env(shell);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "unset") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "echo") == 0)
		shell->exit_code = ft_exec_echo(final_cmd_table->simple_cmd);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "pwd") == 0)
		shell->exit_code = ft_exec_pwd();
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "cd") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "export") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "exit") == 0)
		shell->exit_code = 123;
}

void	handle_builtin(t_shell *shell,
			t_list_d **cmd_table_node, t_final_cmd_table *final_cmd_table)
{
	shell->subshell_pid = 0;
	exec_builtin_cmd(shell, final_cmd_table);
	*cmd_table_node = (*cmd_table_node)->next;
}
