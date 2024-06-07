/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:18:02 by lyeh              #+#    #+#             */
/*   Updated: 2024/06/07 16:30:18 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "clean.h"

static bool	should_execute_next_pipeline(t_sh *shell, t_ct_typ type);
static void	handle_and_or_op(t_sh *shell, t_list_d **cmd_table_node);

void	handle_control_op(t_sh *shell, t_list_d **cmd_table_node)
{
	if (get_cmd_table_type_from_list(*cmd_table_node) == C_PIPE)
		*cmd_table_node = (*cmd_table_node)->next;
	else
		handle_and_or_op(shell, cmd_table_node);
}

static void	handle_and_or_op(t_sh *shell, t_list_d **cmd_table_node)
{
	t_ct_typ	cmd_table_type;

	if (shell->subshell_pid > 0)
		wait_process(shell, shell->subshell_pid);
	cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
	*cmd_table_node = (*cmd_table_node)->next;
	if (!should_execute_next_pipeline(shell, cmd_table_type))
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
