/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:12 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/08 23:21:56 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "clean.h"

// look further and check if no more && or || is found
bool	is_last_pipeline(t_list_d *cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table_node = cmd_table_node->next;
	while (cmd_table_node)
	{
		cmd_table = cmd_table_node->content;
		if (cmd_table->type == C_SUBSHELL_START)
			move_past_subshell(&cmd_table_node);
		if (cmd_table->type == C_AND || cmd_table->type == C_OR)
			return (false);
		cmd_table_node = cmd_table_node->next;
	}
	return (true);
}

void	exec_pipeline(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	while (cmd_table->type != C_AND && cmd_table->type != C_OR)
	{
		if (cmd_table->type == C_SUBSHELL_START)
			handle_subshell(shell, cmd_table_node);
		else if (cmd_table->type == C_SIMPLE_CMD)
			handle_simple_cmd(shell, cmd_table_node);
		else if (cmd_table->type == C_PIPE || cmd_table->type == C_SUBSHELL_END)
			*cmd_table_node = (*cmd_table_node)->next;
		// *cmd_table_node = (*cmd_table_node)->next;
		if (*cmd_table_node == NULL)
			break ;
		cmd_table = (*cmd_table_node)->content;
	}
	// ft_clean_and_exit_shell(shell, shell->exit_code);
}

// TODO: need to stop before next && or || or )
// handle_pipeline = handle_one_pipeline
void	handle_pipeline(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	cmd_table->subshell_pid = fork();
	if (cmd_table->subshell_pid == -1)
		ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	else if (cmd_table->subshell_pid == 0)
		exec_pipeline(shell, cmd_table_node);
	else
	{
		move_to_end_of_pipeline(cmd_table_node);
		// if no more cmd node, 
		// 		need to wait the pipeline pid
		// else
		// 		wait the pipeline pid in handle_control_op
		if (*cmd_table_node)
			broadcast_subshell_pid(*cmd_table_node, cmd_table->subshell_pid);
		else
			wait_process(shell, cmd_table->subshell_pid);
	}
}
