/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:10:43 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/23 02:49:43 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "utils.h"
#include "clean.h"
#include "signals.h"
#include "debug.h"

void	exec_builtin_cmd(t_shell *shell)
{
	t_final_cmd_table	*final_cmd_table;

	final_cmd_table = shell->final_cmd_table;
	if (ft_strcmp(final_cmd_table->simple_cmd[0], "env") == 0)
		shell->exit_code = ft_exec_env(final_cmd_table->env);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "unset") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "echo") == 0)
		shell->exit_code = ft_exec_echo(final_cmd_table->simple_cmd);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "pwd") == 0)
		shell->exit_code = ft_exec_pwd();
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "cd") == 0)
		shell->exit_code = exec_cd(final_cmd_table->simple_cmd,
				&shell->env_list);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "export") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "exit") == 0)
		exec_exit(shell, final_cmd_table->simple_cmd);
}

void	safe_redirect_io_and_exec_builtin(t_shell *shell)
{
	t_final_cmd_table	*final_cmd_table;
	int					saved_std_io[2];
	int					ret;

	final_cmd_table = shell->final_cmd_table;
	// print_final_cmd_table(final_cmd_table);
	ret = SUCCESS;
	if (ft_strcmp(final_cmd_table->simple_cmd[0], "exit") != 0)
	{
		if (!save_std_io(saved_std_io) || \
			!redirect_io(shell))
			ret = SUBSHELL_ERROR;
		else
			exec_builtin_cmd(shell);
		if (!restore_std_io(saved_std_io))
			ret = SUBSHELL_ERROR;
		safe_close(&saved_std_io[0]);
		safe_close(&saved_std_io[1]);
	}
	else
		exec_exit(shell, final_cmd_table->simple_cmd);
	if (ret == SUBSHELL_ERROR)
		raise_error_to_own_subprocess(shell, CREATE_FD_ERROR, NULL);
}

void	handle_builtin(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	if (!handle_io_redirect(shell->final_cmd_table, cmd_table->io_red_list))
	{
		if (shell->subshell_level != 0)
			ft_clean_and_exit_shell(shell, GENERAL_ERROR, NULL);
		else
		{
			shell->exit_code = GENERAL_ERROR;
			*cmd_table_node = (*cmd_table_node)->next;
			return ;
		}
	}
	if (shell->subshell_level == 0)
		safe_redirect_io_and_exec_builtin(shell);
	else
	{
		if (!redirect_io(shell))
			return (raise_error_to_own_subprocess(
					shell, CREATE_FD_ERROR, "fd bind failed"));
		exec_builtin_cmd(shell);
	}
	*cmd_table_node = (*cmd_table_node)->next;
}
