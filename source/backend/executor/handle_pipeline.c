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
	int	cmd_table_type;

	// do T0
	safe_close(shell->new_pipe.read_fd);
	replace_pipe_end(shell->new_pipe.write_fd, shell->old_pipe.write_fd);
	// safe_move_nonempty_pipe(&shell->new_pipe, &shell->old_pipe);
	cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
	while (cmd_table_type != C_AND && cmd_table_type != C_OR && \
		cmd_table_type != C_SUBSHELL_END && cmd_table_type != C_NONE)
	{
		if (cmd_table_type == C_SUBSHELL_START || \
			cmd_table_type == C_SIMPLE_CMD)
		{
			// do T1, handle_pipe
			if (need_pipe(*cmd_table_node) && !create_pipe(&shell->new_pipe))
				ft_clean_and_exit_shell(
					shell, SUBSHELL_ERROR, "exec_pipeline, create pipe failed");
			if (cmd_table_type == C_SUBSHELL_START)
				handle_subshell(shell, cmd_table_node);
			else if (cmd_table_type == C_SIMPLE_CMD)
				handle_simple_cmd(shell, cmd_table_node);
			// do T2.1
			safe_close(shell->new_pipe.write_fd);
			replace_pipe_end(shell->new_pipe.read_fd, shell->old_pipe.read_fd);
		}
		else if (cmd_table_type == C_PIPE)
			// do close old_read?
			*cmd_table_node = (*cmd_table_node)->next;
		cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
	}
	// wait for the last scmd or subshell in the pipeline
	// do T2.2
	// do close old_read?
	// Close both new and old pipe.
	safe_close_pipe(&shell->new_pipe);
	safe_close_pipe(&shell->old_pipe);
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
		// do T2.2
		safe_close_pipe(&shell->new_pipe);
		safe_close_pipe(&shell->old_pipe);
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
			shell, SUBSHELL_ERROR, "handle_pipeline, fork failed");
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
