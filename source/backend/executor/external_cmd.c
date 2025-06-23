/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:17:06 by lyeh              #+#    #+#             */
/*   Updated: 2024/06/07 07:17:29 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "clean.h"
#include "signals.h"

static bool	check_execfile_exist(char *exec_path, char *cmd_name);
static void	reset_external_signal_handler(void);
static void	handle_exec_error(t_sh *shell, char *exec_path);

void	handle_external_cmd(t_sh *shell, t_ct *cmd_table)
{
	t_fct	*final_cmd_table;
	int		ret;

	final_cmd_table = shell->final_cmd_table;
	ret = open_io_files(shell,
			&final_cmd_table->read_fd,
			&final_cmd_table->write_fd, cmd_table->io_red_list);
	if (ret == MALLOC_ERROR)
		raise_error_to_own_subprocess(shell, MALLOC_ERROR, MALLOC_FMSG);
	if (ret != SUCCESS)
		clean_and_exit_shell(shell, GENERAL_ERROR, NULL);
	if (!shell->final_cmd_table->simple_cmd[0])
		clean_and_exit_shell(shell, SUCCESS, NULL);
	if (!check_execfile_exist(final_cmd_table->exec_path,
			final_cmd_table->simple_cmd[0]))
		clean_and_exit_shell(shell, CMD_NOT_FOUND, NULL);
	if (!redirect_scmd_io(shell, &final_cmd_table->read_fd,
			&final_cmd_table->write_fd))
		clean_and_exit_shell(shell, GENERAL_ERROR, NULL);
	reset_external_signal_handler();
	execve(final_cmd_table->exec_path, final_cmd_table->simple_cmd,
		final_cmd_table->env);
	handle_exec_error(shell, final_cmd_table->exec_path);
}

static bool	check_execfile_exist(char *exec_path, char *cmd_name)
{
	if (!exec_path)
		print_error(ERROR_CMD_NOT_FOUND, PROGRAM_NAME, cmd_name);
	else if (access(exec_path, F_OK) != 0 && errno != ENOTDIR)
		print_error("%s: %s: %s\n",
			PROGRAM_NAME, exec_path, strerror(errno));
	else
		return (true);
	return (false);
}

static void	reset_external_signal_handler(void)
{
	setup_signal(SIGINT, SIG_DEFAULT);
	setup_signal(SIGTERM, SIG_DEFAULT);
	setup_signal(SIGUSR1, SIG_DEFAULT);
	setup_signal(SIGQUIT, SIG_DEFAULT);
	setup_signal(SIGPIPE, SIG_DEFAULT);
}

static void	handle_exec_error(t_sh *shell, char *exec_path)
{
	int	error;

	error = errno;
	if (error == ENOEXEC)
		print_error(ERROR_CANNOT_EXEC_FILE,
			PROGRAM_NAME, exec_path, strerror(ENOEXEC));
	else if (is_dir(exec_path))
		print_error("%s: %s: %s\n",
			PROGRAM_NAME, exec_path, strerror(EISDIR));
	else
		print_error("%s: %s: %s\n",
			PROGRAM_NAME, exec_path, strerror(error));
	clean_and_exit_shell(shell, CMD_EXEC_FAILED, NULL);
}
