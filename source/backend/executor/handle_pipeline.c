/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:12 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/14 16:59:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "clean.h"

void	exec_pipeline(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	while (cmd_table->type != C_AND && cmd_table->type != C_OR && \
		cmd_table->type != C_SUBSHELL_END)
	{
		if (cmd_table->type == C_SUBSHELL_START)
			handle_subshell(shell, cmd_table_node);
		else if (cmd_table->type == C_SIMPLE_CMD)
			handle_simple_cmd(shell, cmd_table_node);
		else if (cmd_table->type == C_PIPE)
			*cmd_table_node = (*cmd_table_node)->next;
		if (*cmd_table_node == NULL)
			break ;
		cmd_table = (*cmd_table_node)->content;
	}
	wait_process(shell, shell->subshell_pid);
	ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
}

void	handle_end_of_pipeline(t_shell *shell, t_list_d **cmd_table_node)
{
	int	cmd_table_type;

	cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
	if (is_control_op_cmd_table(cmd_table_type))
		handle_control_op(shell, cmd_table_node);
	else
	{
		wait_process(shell, shell->subshell_pid);
		if (shell->subshell_level != 0)
			ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
	}
}

// handle_pipeline = handle_one_pipeline
void	handle_pipeline(t_shell *shell, t_list_d **cmd_table_node)
{
	shell->subshell_pid = fork();
	if (shell->subshell_pid == -1)
		ft_clean_and_exit_shell(
			shell, GENERAL_ERROR, "handle_pipeline, fork failed");
	else if (shell->subshell_pid == 0)
	{
		shell->subshell_level += 1;
		exec_pipeline(shell, cmd_table_node);
	}
	else
	{
		move_past_pipeline(cmd_table_node);
		handle_end_of_pipeline(shell, cmd_table_node);
	}
}
