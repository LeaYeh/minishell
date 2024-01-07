/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:12 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/07 22:59:57 by lyeh             ###   ########.fr       */
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

// TODO: refactor this function wiith function pointer
void	handle_multi_cmd(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	// while (cmd_table->type != C_SUBSHELL_END && \
	// 	cmd_table->type != C_AND && cmd_table->type != C_OR)
	while (cmd_table->type != C_PIPE)
	{
		if (cmd_table->type == C_SIMPLE_CMD)
			handle_simple_cmd(shell, *cmd_table_node);
		*cmd_table_node = (*cmd_table_node)->next;
		if (*cmd_table_node == NULL)
			break ;
		cmd_table = (*cmd_table_node)->content;
	}
}

// TODO: need to stop before next && or || or )
void	exec_pipeline(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	if (!is_last_pipeline(*cmd_table_node))
	{
		cmd_table = (*cmd_table_node)->content;
		cmd_table->subshell_pid = fork();
		if (cmd_table->subshell_pid == -1)
			ft_clean_and_exit_shell(shell, GENERAL_ERROR);
		else if (cmd_table->subshell_pid == 0)
			handle_multi_cmd(shell, cmd_table_node);
		else
		{
			// We can probably combine these again
			move_to_end_of_pipeline(cmd_table_node);
			broadcast_subshell_pid(*cmd_table_node, cmd_table->subshell_pid);
		}
	}
	else
		handle_multi_cmd(shell, cmd_table_node);
}

void	handle_pipeline_and(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	wait_process(shell, cmd_table->subshell_pid);
	*cmd_table_node = (*cmd_table_node)->next;
	if (shell->exit_code == 0)
		exec_pipeline(shell, cmd_table_node); // Return true or false instead?
	else
	{
		*cmd_table_node = (*cmd_table_node)->next; // not sure if this is correct
		move_to_end_of_pipeline(cmd_table_node);
	}
}

void	handle_pipeline_or(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	wait_process(shell, cmd_table->subshell_pid);
	*cmd_table_node = (*cmd_table_node)->next;
	if (shell->exit_code != 0)
		exec_pipeline(shell, cmd_table_node);
	else
	{
		*cmd_table_node = (*cmd_table_node)->next;
		move_to_end_of_pipeline(cmd_table_node);
	}
}

// The name is confusing, && and || are not part of a pipeline
// handle_pipeline = handle_one_pipeline
void	handle_pipeline(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	if (cmd_table->type == C_SUBSHELL_START)
	{
		handle_subshell(shell, cmd_table_node);
		cmd_table = (*cmd_table_node)->content;
		if (cmd_table->type == C_PIPE)
		{
			*cmd_table_node = (*cmd_table_node)->next;
			cmd_table = (*cmd_table_node)->content;
		}
	}
	if (cmd_table->type == C_SIMPLE_CMD)
		exec_pipeline(shell, cmd_table_node);
	else if (cmd_table->type == C_AND)
		handle_pipeline_and(shell, cmd_table_node);
	else if (cmd_table->type == C_OR)
		handle_pipeline_or(shell, cmd_table_node);
	// move past the pipeline
	// *cmd_table_node = (*cmd_table_node)->next;
}

// bool	handle_pipeline(t_shell *shell, t_list_d **cmd_table_list)
// {
// 	int	i;
// 	int	*pid_array;

// 	pid_array = malloc(sizeof(int) * get_pipline_count(cmd_table_list));
// 	if (!pid_array)
// 		return (false);
// 	i = 0;
// 	while (cmd_table_list)
// 	{
// 		if (i == 0 || need_next_pipline(cmd_table_list))
// 		{
// 			waitpid(pid_array[i], &shell->exit_status, 0);
// 			if (WIFEXITED(shell->exit_status))
// 				shell->exit_code = WEXITSTATUS(shell->exit_status);
// 			if (get_cmd_table_type_from_list(cmd_table_list) == C_AND && \
// 				shell->exit_code == 0)
// 				exec_pipeline(shell, cmd_table_list->next);
// 			else if (get_cmd_table_type_from_list(cmd_table_list) == C_OR && \
// 				shell->exit_code != 0)
// 				exec_pipeline(shell, cmd_table_list->next);
// 		}
// 		cmd_table_list = cmd_table_list->next;
// 	}
// 	return (free(pid_array), true);
// }
