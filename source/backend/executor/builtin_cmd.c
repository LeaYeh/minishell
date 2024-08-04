/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:10:43 by lyeh              #+#    #+#             */
/*   Updated: 2024/06/07 07:23:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "utils.h"
#include "clean.h"
#include "signals.h"

static void	safe_redirect_io_and_exec_builtin(t_sh *shell);
static void	redirect_io_and_exec_builtin(t_sh *shell);
static void	exec_builtin_cmd(t_sh *shell);

void	handle_builtin(t_sh *shell, t_list_d **cmd_table_node)
{
	t_ct	*cmd_table;
	int		ret;

	cmd_table = (*cmd_table_node)->content;
	ret = open_io_files(shell,
			&shell->final_cmd_table->read_fd,
			&shell->final_cmd_table->write_fd, cmd_table->io_red_list);
	if (ret == MALLOC_ERROR)
		raise_error_to_own_subprocess(shell, MALLOC_ERROR, MALLOC_FMSG);
	else if (ret != SUCCESS)
	{
		shell->exit_code = GENERAL_ERROR;
		if (shell->subshell_level != 0)
			clean_and_exit_shell(shell, shell->exit_code, NULL);
	}
	else if (shell->final_cmd_table->simple_cmd[0] && \
				shell->subshell_level == 0)
		safe_redirect_io_and_exec_builtin(shell);
	else if (shell->final_cmd_table->simple_cmd[0])
		redirect_io_and_exec_builtin(shell);
	if (shell->exit_code == MALLOC_ERROR)
		raise_error_to_own_subprocess(shell, shell->exit_code, NULL);
	*cmd_table_node = (*cmd_table_node)->next;
}

static void	safe_redirect_io_and_exec_builtin(t_sh *shell)
{
	t_fct	*final_cmd_table;
	int		saved_std_io[2];
	bool	ret;

	final_cmd_table = shell->final_cmd_table;
	ret = true;
	if (ft_strcmp(final_cmd_table->simple_cmd[0], "exit") != 0)
	{
		if (!save_std_io(saved_std_io) || \
			!redirect_scmd_io(shell, &final_cmd_table->read_fd,
				&final_cmd_table->write_fd))
			ret = false;
		else
			exec_builtin_cmd(shell);
		if (!restore_std_io(saved_std_io))
			ret = false;
		safe_close(&saved_std_io[0]);
		safe_close(&saved_std_io[1]);
	}
	else
		exec_exit(shell, final_cmd_table->simple_cmd);
	if (!ret)
		raise_error_to_own_subprocess(shell, GENERAL_ERROR, NULL);
}

static void	redirect_io_and_exec_builtin(t_sh *shell)
{
	if (!redirect_scmd_io(shell, &shell->final_cmd_table->read_fd,
			&shell->final_cmd_table->write_fd))
		raise_error_to_own_subprocess(
			shell, GENERAL_ERROR, "fd redirect failed");
	exec_builtin_cmd(shell);
}

static void	exec_builtin_cmd(t_sh *shell)
{
	t_fct	*final_cmd_table;

	final_cmd_table = shell->final_cmd_table;
	if (ft_strcmp(final_cmd_table->simple_cmd[0], "env") == 0)
		shell->exit_code = exec_env(final_cmd_table->env);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "unset") == 0)
		shell->exit_code = exec_unset(final_cmd_table->simple_cmd,
				&shell->env_list);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "echo") == 0)
		shell->exit_code = exec_echo(shell, final_cmd_table->simple_cmd);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "pwd") == 0)
		shell->exit_code = exec_pwd(shell);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "cd") == 0)
		shell->exit_code = exec_cd(shell,
				final_cmd_table->simple_cmd, &shell->env_list);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "export") == 0)
		shell->exit_code = exec_export(shell,
				final_cmd_table->simple_cmd, &shell->env_list);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "exit") == 0)
		exec_exit(shell, final_cmd_table->simple_cmd);
	else if (ft_strcmp(final_cmd_table->simple_cmd[0], "~") == 0 && \
			shell->is_interactive)
		shell->exit_code = exec_easter_egg();
}
