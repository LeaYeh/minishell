/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:04:52 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/24 02:38:15 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "heredoc.h"
#include "clean.h"
#include "utils.h"
#include "debug.h"
#include "signals.h"

void	handle_cmd_execution(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	if (!set_final_cmd_table(shell, cmd_table))
	{
		raise_error_to_own_subprocess(shell, MALLOC_ERROR, "malloc failed");
		move_past_pipeline(cmd_table_node);
		return ;
	}
	if (is_builtin(shell->final_cmd_table->simple_cmd[0]) && \
		!is_scmd_in_pipeline(*cmd_table_node))
		handle_builtin(shell, cmd_table_node);
	else
		handle_pipeline(shell, cmd_table_node);
}

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
		else if (cmd_table->type == C_SIMPLE_CMD)
			handle_cmd_execution(shell, &cmd_table_node);
		else if (cmd_table->type == C_SUBSHELL_START)
			handle_pipeline(shell, &cmd_table_node);
		else
			raise_error_and_escape(shell, "unexpected unknown command type");
	}
}

// TODO: activate signal listener in the child process
void	ft_executor(t_shell *shell)
{
	int	heredoc_status;

	setup_signal(shell, SIGINT, SIG_HEREDOC);
	heredoc_status = ft_heredoc(shell);
	setup_signal(shell, SIGINT, SIG_STD);
	if (heredoc_status == HEREDOC_ERROR)
		ft_clean_and_exit_shell(shell, MALLOC_ERROR, "heredoc malloc/fd error");
	else if (heredoc_status == HEREDOC_ABORT)
		return ;
	handle_process(shell, shell->cmd_table_list);
}
