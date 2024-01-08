/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_control_op.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:09:07 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/08 21:51:14 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "clean.h"

bool	match_and_or_condition(int type, int exit_code)
{	
	if (type == C_AND && exit_code == 0)
		return (true);
	else if (type == C_OR && exit_code != 0)
		return (true);
	return (false);
}

void	handle_and_or_op(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	if (cmd_table->subshell_pid != -1)
		wait_process(shell, cmd_table->subshell_pid);
	*cmd_table_node = (*cmd_table_node)->next;
	if (!match_and_or_condition(cmd_table->type, shell->exit_code))
		move_past_pipeline(cmd_table_node);
}

void    handle_control_op(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	if (cmd_table->type == C_PIPE) // means ignore, not handle
        *cmd_table_node = (*cmd_table_node)->next; // (echo 1) | echo 2
	else
		handle_and_or_op(shell, cmd_table_node);
}
