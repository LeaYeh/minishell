/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:04:52 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/19 22:48:58 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "clean.h"
#include "utils.h"
#include "debug.h"

void	handle_cmd_execution(t_shell *shell, t_list_d **cmd_table_node)
{
	t_final_cmd_table	*final_cmd_table;

	final_cmd_table = get_final_cmd_table(shell, (*cmd_table_node)->content);
	if (!final_cmd_table)
		ft_clean_and_exit_shell(
			shell, PREPROCESS_ERROR, "final cmd table malloc failed");
	if (is_builtin(final_cmd_table->simple_cmd[0]) && \
		!is_scmd_in_pipeline(*cmd_table_node))
	{
		print_final_cmd_table(final_cmd_table);
		handle_builtin(shell, cmd_table_node, final_cmd_table);
		free_final_cmd_table(&final_cmd_table);
	}
	else
	{
		free_final_cmd_table(&final_cmd_table);
		handle_pipeline(shell, cmd_table_node);
	}
}

void	handle_process(t_shell *shell, t_list_d *cmd_table_node)
{
	t_cmd_table			*cmd_table;

	while (cmd_table_node)
	{
		cmd_table = cmd_table_node->content;
		if (cmd_table->type == C_SUBSHELL_END)
			ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
		else if (is_control_op_cmd_table(cmd_table->type))
			handle_control_op(shell, &cmd_table_node);
		else if (cmd_table->type == C_SIMPLE_CMD)
			handle_cmd_execution(shell, &cmd_table_node);
		else if (cmd_table->type == C_SUBSHELL_START)
			handle_pipeline(shell, &cmd_table_node);
		else
			ft_clean_and_exit_shell(shell,
				PREPROCESS_ERROR, "handle process, unknown command type");
	}
}

// TODO: activate signal listener in the child process
void	ft_executor(t_shell *shell)
{
	if (!ft_heredoc(shell->cmd_table_list))
		ft_clean_and_exit_shell(
			shell, PREPROCESS_ERROR, "heredoc malloc failed");
	handle_process(shell, shell->cmd_table_list);
}
