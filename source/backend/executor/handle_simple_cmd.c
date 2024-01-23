/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:15 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/23 16:22:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "utils.h"
#include "clean.h"
#include "debug.h"

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
void	exec_simple_cmd(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table			*cmd_table;
	t_final_cmd_table	*final_cmd_table;

	cmd_table = get_cmd_table_from_list(*cmd_table_node);
	final_cmd_table = get_final_cmd_table(shell, cmd_table);
	if (!final_cmd_table)
		ft_clean_and_exit_shell(
			shell, SUBSHELL_ERROR, "get_final_cmd_table failed");
	if (final_cmd_table->simple_cmd[0] == NULL)
		printf("\n");
	else if (is_builtin(final_cmd_table->simple_cmd[0]))
		handle_builtin(shell, cmd_table_node, final_cmd_table);
	else
		handle_external_cmd(shell, final_cmd_table);
	free_final_cmd_table(&final_cmd_table);
	ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
}

// TODO: Need to handle the pipe redirct in first subshell process
// TODO: And all the process need to close all the unuse read end -> how
void	handle_simple_cmd(t_shell *shell, t_list_d **cmd_table_node)
{
	shell->subshell_pid = fork();
	if (shell->subshell_pid == -1)
		ft_clean_and_exit_shell(
			shell, SUBSHELL_ERROR, "handle_simple_cmd, fork failed");
	else if (shell->subshell_pid == 0)
	{
		shell->subshell_level += 1;
		// do T0
		handle_pipes_child(&shell->new_pipe, &shell->old_pipe);
		exec_simple_cmd(shell, cmd_table_node);
	}
	else
		*cmd_table_node = (*cmd_table_node)->next;
}
