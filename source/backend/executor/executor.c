/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:04:52 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/11 17:33:35 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "clean.h"
#include "utils.h"

void	handle_process(t_shell *shell, t_list_d *cmd_table_node)
{
	t_cmd_table	*cmd_table;

	while (cmd_table_node)
	{
		cmd_table = cmd_table_node->content;
		if (cmd_table->type == C_SUBSHELL_END)
			ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
		else if (is_control_op_cmd_table(cmd_table->type))
			handle_control_op(shell, &cmd_table_node);
		else if (cmd_table->type == C_SIMPLE_CMD || cmd_table->type == C_SUBSHELL_START)
		{
			if (is_builtin(cmd_table) && !is_scmd_in_pipeline(cmd_table_node))
				handle_builtin(shell, &cmd_table_node);
			else
				handle_pipeline(shell, &cmd_table_node);
		}
		else // it should not happen -> general error
			ft_clean_and_exit_shell(
				shell, GENERAL_ERROR, "handle process, unknown command type");
	}
}

// TODO: activate signal listener in the child process
void	ft_executor(t_shell *shell)
{
	if (!ft_heredoc(shell->cmd_table_list))
		ft_clean_and_exit_shell(shell, GENERAL_ERROR, "heredoc malloc failed");
	handle_process(shell, shell->cmd_table_list);
}
