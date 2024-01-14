/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:51:03 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/14 16:39:46 by codespace        ###   ########.fr       */
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
		move_past_subshell(cmd_table_node);
}
