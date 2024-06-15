/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:04:52 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 22:45:04 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "heredoc.h"
#include "clean.h"
#include "utils.h"
#include "signals.h"

static void	handle_cmd_execution(t_sh *shell, t_list_d **cmd_table_node);
static void	handle_simple_cmd(t_sh *shell, t_list_d **cmd_table_node);

void	executor(t_sh *shell)
{
	t_hd_st	heredoc_status;

	heredoc_status = heredoc(shell);
	if (heredoc_status == HD_ERROR)
		clean_and_exit_shell(shell, MALLOC_ERROR, "heredoc malloc/fd error");
	else if (heredoc_status == HD_ABORT)
		return ;
	handle_process(shell, shell->cmd_table_list);
}

void	handle_process(t_sh *shell, t_list_d *cmd_table_node)
{
	t_ct	*cmd_table;

	while (cmd_table_node)
	{
		cmd_table = cmd_table_node->content;
		if (cmd_table->type == C_SUBSHELL_END)
			clean_and_exit_shell(shell, shell->exit_code, NULL);
		else if (is_control_op_cmd_table(cmd_table->type))
			handle_control_op(shell, &cmd_table_node);
		else if (cmd_table->type == C_SIMPLE_CMD)
			handle_cmd_execution(shell, &cmd_table_node);
		else if (cmd_table->type == C_SUBSHELL_START)
			fork_pipeline(shell, &cmd_table_node);
		else
			raise_error_and_escape(shell, "unexpected unknown command type");
	}
}

static void	handle_cmd_execution(t_sh *shell, t_list_d **cmd_table_node)
{
	if (is_scmd_in_pipeline(*cmd_table_node))
		fork_pipeline(shell, cmd_table_node);
	else
		handle_simple_cmd(shell, cmd_table_node);
}

static void	handle_simple_cmd(t_sh *shell, t_list_d **cmd_table_node)
{
	char	*cmd_name;
	t_ct	*cmd_table;
	int		ret;

	cmd_table = (*cmd_table_node)->content;
	ret = set_expanded_cmd_name(&cmd_name, shell, cmd_table->simple_cmd_list);
	if (ret != SUCCESS)
		return (free(cmd_name),
			handle_expansion_error(shell, cmd_table_node, ret));
	if (!cmd_name || is_builtin(cmd_name, shell))
	{
		free(cmd_name);
		if (set_final_cmd_table(shell, cmd_table) != SUCCESS)
			return (handle_expansion_error(
					shell, cmd_table_node, MALLOC_ERROR));
		handle_builtin(shell, cmd_table_node);
		free_final_cmd_table(&shell->final_cmd_table);
	}
	else
	{
		free(cmd_name);
		fork_pipeline(shell, cmd_table_node);
	}
}
