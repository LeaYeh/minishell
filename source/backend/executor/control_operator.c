/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:18:02 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 17:44:06 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "clean.h"

static bool	should_execute_next_pipeline(t_sh *shell, t_ct_typ type);
static void	handle_and_or_op(t_sh *shell, t_list_d **cmd_table_node);

void	handle_control_op(t_sh *shell, t_list_d **cmd_table_node)
{
	t_ct	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	if (cmd_table->type == C_PIPE)
		*cmd_table_node = (*cmd_table_node)->next;
	else
		handle_and_or_op(shell, cmd_table_node);
}

static void	handle_and_or_op(t_sh *shell, t_list_d **cmd_table_node)
{
	t_ct	*cmd_table;

	if (shell->subshell_pid > 0)
		wait_process(shell, shell->subshell_pid);
	cmd_table = (*cmd_table_node)->content;
	*cmd_table_node = (*cmd_table_node)->next;
	if (!should_execute_next_pipeline(shell, cmd_table->type))
		move_past_pipeline(cmd_table_node);
}

static bool	should_execute_next_pipeline(t_sh *shell, t_ct_typ type)
{
	if (shell->signal_record != 0)
	{
		shell->exit_code = TERM_BY_SIGNAL + shell->signal_record;
		return (false);
	}
	if (shell->exit_code == TERM_BY_SIGNAL + SIGINT)
		return (false);
	if (type == C_AND && shell->exit_code == 0)
		return (true);
	else if (type == C_OR && shell->exit_code != 0)
		return (true);
	return (false);
}
