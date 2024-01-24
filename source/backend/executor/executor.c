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
#include "defines.h"
#include "clean.h"
#include "utils.h"
#include "debug.h"

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
		{
			if (is_builtin(cmd_table->simple_cmd_list->content) && \
				!is_scmd_in_pipeline(cmd_table_node))
				handle_builtin(shell, &cmd_table_node);
			else
				handle_pipeline(shell, &cmd_table_node);
		}
		else if (cmd_table->type == C_SUBSHELL_START)
			handle_pipeline(shell, &cmd_table_node);
		else
			ft_clean_and_exit_shell(shell,
				PREPROCESS_ERROR, "handle process, unknown command type");
	}
}

bool	pre_expand_simple_cmd(t_shell *shell, t_list_d *cmd_table_node)
{
	t_cmd_table	*cmd_table;
	t_list		*expanded_list;
	int			ret;

	expanded_list = NULL;
	while (cmd_table_node)
	{
		cmd_table = cmd_table_node->content;
		if (!cmd_table->simple_cmd_list)
			return (true);
		ret = expand_list(shell, cmd_table->simple_cmd_list, &expanded_list);
		if (ret == SUBSHELL_ERROR)
			return (ft_lstclear(&expanded_list, free), false);
		else if (ret == BAD_SUBSTITUTION)
			ft_lstclear(&expanded_list, free);
		ft_lstclear(&cmd_table->simple_cmd_list, free);
		cmd_table->simple_cmd_list = expanded_list;
		cmd_table_node = cmd_table_node->next;
	}
	return (true);
}

// TODO: activate signal listener in the child process
void	ft_executor(t_shell *shell)
{
	if (!ft_heredoc(shell->cmd_table_list) || \
		!pre_expand_simple_cmd(shell, shell->cmd_table_list))
		ft_clean_and_exit_shell(
			shell, PREPROCESS_ERROR, "heredoc/expend malloc failed");
	print_cmd_table_list(shell->cmd_table_list);
	handle_process(shell, shell->cmd_table_list);
}
