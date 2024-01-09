/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:15 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/09 20:09:16 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "utils.h"
#include "clean.h"

/*
1. [ ] do expansions
	* If there is a command name left after expansion, execution proceeds as described below. Otherwise, the command exits.
	* If one of the expansions contained a command substitution,
		the exit status of the command is the exit status of the last command substitution performed.
	* If there were no command substitutions, the command exits with a status of zero.
2. [ ] do assginments
	* If no command name results, the variable assignments affect the current shell environment.
	* assignment statements are performed before redirections.
		Otherwise, the variables are added to the environment of the executed command and do not affect the current shell environment.
3. [ ] do redirections
	* If no command name results, redirections are performed, but do not affect the current shell environment.
	* A redirection error causes the command to exit with a non-zero status.
4. [ ] do command

*/
void	exec_simple_cmd(t_shell *shell, t_list_d *cmd_table_node)
{
	(void)shell;
	(void)cmd_table_node;
	exit(0);
}

// TODO: Meed to handle the pipe redirct in first subshell process
// TODO: And all the process need to close all the unuse read end -> how

void	handle_simple_cmd(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	shell->subshell_pid = fork();
	if (shell->subshell_pid == -1)
		ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	else if (shell->subshell_pid == 0)
		exec_simple_cmd(shell, *cmd_table_node);
	else
	{
		// if (is_last_simple_cmd(cmd_table_node))
		// 	wait_process(shell, shell->subshell_pid);
		*cmd_table_node = (*cmd_table_node)->next;
	}
}

// before fork, setup pipes for current simple cmd and next simple cmd
// setup_pipe(cmd_table_node, get_next_simple_cmd_node(cmd_table_node));
// TODO: When to close pipe? in parent
// 		-> after fork in parent, close write end of pipe
// void	handle_simple_cmd(t_shell *shell, t_list_d *cmd_table_node)
// {
// 	t_cmd_table	*cmd_table;

// 	cmd_table = cmd_table_node->content;
// 	if (cmd_table->subshell_level > 0)
// 		if (!setup_subshell_pipe(cmd_table_node))
// 			ft_clean_and_exit_shell(shell, GENERAL_ERROR);
// 	if (!is_last_simple_cmd(cmd_table_node))
// 	{
// 		if (!setup_normal_pipe(cmd_table_node))
// 			ft_clean_and_exit_shell(shell, GENERAL_ERROR);
// 		cmd_table->simple_cmd_pid = fork();
// 		if (cmd_table->simple_cmd_pid == -1)
// 			ft_clean_and_exit_shell(shell, GENERAL_ERROR);
// 		else if (cmd_table->simple_cmd_pid == 0)
// 			exec_simple_cmd(shell, cmd_table_node);
// 		// TODO: close pipe in parent
// 		// else
// 		// 	close_pipe(cmd_table_node);
// 	}
// 	else
// 		exec_simple_cmd(shell, cmd_table_node);
// }
