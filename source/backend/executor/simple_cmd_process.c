/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:15 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 17:44:12 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "utils.h"
#include "clean.h"
#include "signals.h"

static void	exec_simple_cmd(t_sh *shell, t_list_d **cmd_table_node);

void	fork_simple_cmd(t_sh *shell, t_list_d **cmd_table_node)
{
	shell->subshell_pid = fork();
	if (shell->subshell_pid == -1)
		raise_error_to_all_subprocess(
			shell, FORK_ERROR, "simple_cmd fork failed");
	else if (shell->subshell_pid == 0)
	{
		shell->subshell_level += 1;
		handle_pipes_child(&shell->new_pipe, &shell->old_pipe);
		exec_simple_cmd(shell, cmd_table_node);
	}
	else
		*cmd_table_node = (*cmd_table_node)->next;
}

static void	exec_simple_cmd(t_sh *shell, t_list_d **cmd_table_node)
{
	int			ret;

	ret = set_final_cmd_table(shell, (*cmd_table_node)->content);
	if (ret == MALLOC_ERROR)
		raise_error_to_own_subprocess(shell, MALLOC_ERROR, MALLOC_FMSG);
	if (ret == BAD_SUBSTITUTION)
		shell->exit_code = BAD_SUBSTITUTION;
	else if (is_builtin(shell->final_cmd_table->simple_cmd[0], shell))
	{
		setup_signal(shell, SIGPIPE, SIG_IGNORE);
		handle_builtin(shell, cmd_table_node);
	}
	else
		handle_external_cmd(shell, get_cmd_table_from_list(*cmd_table_node));
	clean_and_exit_shell(shell, shell->exit_code, NULL);
}
