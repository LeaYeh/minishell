/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:04:52 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/07 17:27:15 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "clean.h"
#include "utils.h"

void	handle_process(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	while (*cmd_table_node)
	{
		cmd_table = (*cmd_table_node)->content;
		if (cmd_table->type == C_SUBSHELL_END)
			ft_clean_and_exit_shell(shell, shell->exit_code);
		// if (cmd_table->type == C_SUBSHELL_START)
		// 	handle_subshell(shell, cmd_table_node);
		// I think C_AND and C_OR should be separated so they can return a bool
		// They also need to handle the following case: (echo 1) && echo 2
		// else if (is_first_simple_cmd(*cmd_table_node) || \
		// 	(cmd_table->type == C_AND || cmd_table->type == C_OR))
		else if (cmd_table->type == C_SIMPLE_CMD || \
			cmd_table->type == C_AND || cmd_table->type == C_OR)
			handle_pipeline(shell, cmd_table_node);
		else
			*cmd_table_node = (*cmd_table_node)->next;
		// We always move past the pipeline.
		// So maybe we don't need to check if is_first_simple_cmd.
		// else if (cmd_table->type == C_PIPE)
		// 	*cmd_table_node = (*cmd_table_node)->next;
		// else
		// 	handle_pipeline(shell, cmd_table_node);
	}
}

// void	handle_process(t_shell *shell, t_list_d **cmd_table_node)
// {
// 	t_cmd_table	*cmd_table;

// 	while (*cmd_table_node)
// 	{
// 		cmd_table = (*cmd_table_node)->content;
// 		if (cmd_table->type == C_SUBSHELL_END || \
// 				cmd_table->type == C_AND || cmd_table->type == C_OR)
// 			ft_clean_and_exit_shell(shell, shell->exit_code);
// 		if (cmd_table->type == C_SUBSHELL_START)
// 		{
// 			handle_subshell(shell, cmd_table_node);
// 			move_past_subshell(cmd_table_node);
// 		}
// 		else if (is_first_simple_cmd(*cmd_table_node))
// 			handle_pipeline(shell, cmd_table_node);
// 		else
// 			*cmd_table_node = (*cmd_table_node)->next;
// 	}
// }

// TODO: exit code =??? when here doc fails
// ignore ctrl-D
// fork? (maybe move the fork from handle_all_cmd_table to here)
// activate signal listener in the child process
void	ft_executor(t_shell *shell)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	else if (pid == 0)
	{
		if (!ft_heredoc(shell->cmd_table_list))
			ft_clean_and_exit_shell(shell, GENERAL_ERROR);
		handle_process(shell, &shell->cmd_table_list);
	}
	else
		wait_process(shell, pid);
	// ft_clean_shell(shell, EXIT_SUCCESS);
}
