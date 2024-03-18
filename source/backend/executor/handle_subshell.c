/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:51:03 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/23 16:22:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "utils.h"
#include "clean.h"
#include "signals.h"

void	handle_subshell(t_shell *shell, t_list_d **cmd_table_node)
{
	int	ret;

	shell->subshell_pid = fork();
	if (shell->subshell_pid == -1)
		raise_error_to_all_subprocess(
			shell, FORK_ERROR, "subshell fork failed");
	else if (shell->subshell_pid == 0)
	{
		shell->subshell_level += 1;
		handle_pipes_child(&shell->new_pipe, &shell->old_pipe);
		ret = redirect_subshell_io(
				shell, get_cmd_table_from_list(*cmd_table_node));
		if (ret == MALLOC_ERROR)
			raise_error_to_own_subprocess(shell, MALLOC_ERROR, "malloc failed");
		if (ret == GENERAL_ERROR)
			ft_clean_and_exit_shell(shell, GENERAL_ERROR, NULL);
		*cmd_table_node = (*cmd_table_node)->next;
		handle_process(shell, *cmd_table_node);
	}
	else
		move_past_subshell(cmd_table_node);
}
