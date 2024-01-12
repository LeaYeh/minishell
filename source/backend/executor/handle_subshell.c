/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:51:03 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/11 17:36:17 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "utils.h"
#include "clean.h"

void	handle_subshell(t_shell *shell, t_list_d **cmd_table_node)
{
	shell->subshell_pid = fork();
	if (shell->subshell_pid == -1)
		ft_clean_and_exit_shell(shell, GENERAL_ERROR, "subshell fork failed");
	else if (shell->subshell_pid == 0)
	{
		shell->subshell_level += 1;
		*cmd_table_node = (*cmd_table_node)->next;
		handle_process(shell, *cmd_table_node);
	}
	else
	{
		move_to_end_of_subshell(cmd_table_node);
		if (get_cmd_table_type_from_list((*cmd_table_node)->next) == C_PIPE)
			*cmd_table_node = (*cmd_table_node)->next;
		else
		{
			wait_process(shell, shell->subshell_pid);
			if (shell->subshell_level != 0)
				ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
		}
	}
}
