/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:04:52 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/09 16:49:49 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "clean.h"
#include "utils.h"

// how to make sure the parent process waiting for the last child process?
// 	-> by broadcast pid and wait at the correct position!
// 
// who will fork new process? -> handle_subshell and handle_pipeline will always fork
// 	- when the handle_subshell exit?
// 		-> after the parent move_past_subshell?
// 	- when the handle_pipeline exit?
// 		-> after the parent move_past_pipeline?
void	handle_process(t_shell *shell, t_list_d *cmd_table_node)
{
	t_cmd_table	*cmd_table;

	while (cmd_table_node)
	{
		cmd_table = cmd_table_node->content;
		if (cmd_table->type == C_SUBSHELL_END)
			ft_clean_and_exit_shell(shell, shell->exit_code);
		else if (cmd_table->type == C_SUBSHELL_START)
			handle_subshell(shell, &cmd_table_node);
		else if (is_control_op_cmd_table(cmd_table->type))
			handle_control_op(shell, &cmd_table_node);
		else if (cmd_table->type == C_SIMPLE_CMD)
		{
			if (is_builtin(cmd_table) && !is_scmd_in_pipeline(cmd_table_node))
				shell->exit_code = handle_builtin(shell, &cmd_table_node);
			else
				handle_pipeline(shell, &cmd_table_node);	
		}
		else // it should not happen -> general error
			ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	}
}

// TODO: activate signal listener in the child process
void	ft_executor(t_shell *shell)
{
	if (!ft_heredoc(shell->cmd_table_list))
		ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	handle_process(shell, shell->cmd_table_list);
}
