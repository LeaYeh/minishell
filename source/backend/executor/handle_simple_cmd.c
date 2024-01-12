/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:15 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/11 21:24:42 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "utils.h"
#include "clean.h"
#include "debug.h"

void	exec_external_cmd(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	// TODO: need to bind the fds to stdin and stdout, if bind failed then exit
	if (!check_executable(final_cmd_table->cmd_name))
		ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
	execve(final_cmd_table->cmd_name, final_cmd_table->cmd_args,
			final_cmd_table->envp);
	free_final_cmd_table(&final_cmd_table); // should not reach here, but still need to close the fds
	ft_clean_and_exit_shell(shell, CMD_EXEC_FAILED, NULL);
}

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
void	handle_external_cmd(t_shell *shell, t_cmd_table *cmd_table)
{
	t_final_cmd_table	*final_cmd_table;

	final_cmd_table = get_final_cmd_table(shell, cmd_table);
	if (!final_cmd_table)
	{
		shell->exit_code = GENERAL_ERROR;
		return ;
	}
	exec_external_cmd(shell, final_cmd_table);
}

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
		handle_external_cmd(shell, cmd_table);
	exit(shell->exit_code);
}

// TODO: Need to handle the pipe redirct in first subshell process
// TODO: And all the process need to close all the unuse read end -> how
void	handle_simple_cmd(t_shell *shell, t_list_d **cmd_table_node)
{
	shell->subshell_pid = fork();
	if (shell->subshell_pid == -1)
		ft_clean_and_exit_shell(
			shell, GENERAL_ERROR, "handle_simple_cmd, fork failed");
	else if (shell->subshell_pid == 0)
	{
		shell->subshell_level += 1;
		exec_simple_cmd(shell, cmd_table_node);
	}
	else
		*cmd_table_node = (*cmd_table_node)->next;
}
