/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:51:03 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/09 01:38:36 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "utils.h"
#include "clean.h"

// 
void	handle_subshell(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	cmd_table->subshell_pid = fork();
	if (cmd_table->subshell_pid == -1)
		ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	else if (cmd_table->subshell_pid == 0)
	{
		*cmd_table_node = (*cmd_table_node)->next;
		handle_process(shell, *cmd_table_node);
	}
	else
	{
		// move_past_subshell(cmd_table_node);
		move_to_end_of_subshell(cmd_table_node);
		broadcast_subshell_pid(*cmd_table_node, cmd_table->subshell_pid);
	}
}

// void	handle_subshell(t_shell *shell, t_list_d **cmd_table_node)
// {
// 	static int	subshell_pid = 0;
// 	int			cmd_table_type;

// 	cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
// 	if (cmd_table_type == C_SUBSHELL_START)
// 	{
// 		subshell_pid = fork();
// 		if (subshell_pid == -1)
// 		{
// 			ft_clean_shell(shell);
// 			exit(GENERAL_ERROR);
// 		}
// 		else if (subshell_pid == 0)
// 		{
// 			*cmd_table_node = (*cmd_table_node)->next;
// 			handle_process(shell, *cmd_table_node);
// 		}
// 	}
// 	else if (cmd_table_type == C_SUBSHELL_END && subshell_pid != 0)
// 	{
// 		wait_process(shell, subshell_pid);
// 		subshell_pid = 0;
// 	}
// }

