/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:15 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/11 17:36:39 by lyeh             ###   ########.fr       */
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
void	exec_simple_cmd(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = get_cmd_table_from_list(*cmd_table_node);
	if (cmd_table->type != C_SIMPLE_CMD)
		ft_clean_and_exit_shell(
			shell, GENERAL_ERROR, "exec simple cmd, not simple cmd");
	if (is_builtin(cmd_table))
		handle_builtin(shell, cmd_table_node);
	else
	{
		// bind fd
		// check cmd error
		// execev
		// close fd
	}
	exit(shell->exit_code);
}

// TODO: Need to handle the pipe redirct in first subshell process
// TODO: And all the process need to close all the unuse read end -> how
void	handle_simple_cmd(t_shell *shell, t_list_d **cmd_table_node)
{
	shell->subshell_pid = fork();
	if (shell->subshell_pid == -1)
		ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	else if (shell->subshell_pid == 0)
	{
		shell->subshell_level += 1;
		exec_simple_cmd(shell, cmd_table_node);
	}
	else
		*cmd_table_node = (*cmd_table_node)->next;
}
