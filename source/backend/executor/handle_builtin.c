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

void	exec_builtin_cmd(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	if (ft_strcmp(final_cmd_table->simple_cmd[0], "env") == 0)
		shell->exit_code = ft_exec_env(shell);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "unset") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "echo") == 0)
		shell->exit_code = ft_exec_echo(final_cmd_table->simple_cmd);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "pwd") == 0)
		shell->exit_code = ft_exec_pwd();
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "cd") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "export") == 0)
		shell->exit_code = 123;
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "exit") == 0)
		exec_exit(shell, final_cmd_table);
}

void	safe_redirect_io_and_exec_builtin(
	t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	int	saved_std_io[2];
	int	ret;

	ret = SUCCESS;
	if (ft_strcmp(final_cmd_table->simple_cmd[0], "exit") != 0)
	{
		if (!save_std_io(saved_std_io) || \
			!redirect_io(shell, final_cmd_table))
			ret = SUBSHELL_ERROR;
		else
			exec_builtin_cmd(shell, final_cmd_table);
		if (!restore_std_io(saved_std_io))
			ret = SUBSHELL_ERROR;
		safe_close(&saved_std_io[0]);
		safe_close(&saved_std_io[1]);
	}
	else
		exec_exit(shell, final_cmd_table);
	if (ret == SUBSHELL_ERROR)
	{
		free_final_cmd_table(&final_cmd_table);
		raise_internal_error(shell, NULL);
	}
}

void	handle_builtin(t_shell *shell, t_list_d **cmd_table_node)
{
	t_final_cmd_table	*final_cmd_table;

	final_cmd_table = get_final_cmd_table(shell, (*cmd_table_node)->content);
	if (final_cmd_table)
	{
		if (shell->subshell_level == 0)
			safe_redirect_io_and_exec_builtin(shell, final_cmd_table);
		else
		{
			if (!redirect_io(shell, final_cmd_table))
			{
				return (free_final_cmd_table(&final_cmd_table),
					raise_internal_error(shell, NULL));
			}
			exec_builtin_cmd(shell, final_cmd_table);
		}
		free_final_cmd_table(&final_cmd_table);
	}
	*cmd_table_node = (*cmd_table_node)->next;
}
