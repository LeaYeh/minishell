/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:09:45 by lyeh              #+#    #+#             */
/*   Updated: 2024/06/07 07:37:45 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"

bool	save_std_io(int saved_std_io[2])
{
	saved_std_io[0] = dup(STDIN_FILENO);
	if (saved_std_io[0] != -1)
		saved_std_io[1] = dup(STDOUT_FILENO);
	else
		saved_std_io[1] = -1;
	if (saved_std_io[1] == -1)
	{
		perror(PROGRAM_NAME);
		safe_close(&saved_std_io[0]);
		return (false);
	}
	return (true);
}

bool	redirect_scmd_io(t_sh *shell, int *read_fd, int *write_fd)
{
	bool	ret;

	ret = true;
	if (dup2(*read_fd, STDIN_FILENO) == -1 || \
		dup2(*write_fd, STDOUT_FILENO) == -1)
	{
		perror(PROGRAM_NAME);
		ret = false;
	}
	if (shell->subshell_level != 0)
	{
		safe_close_all_pipes(shell);
		safe_close(read_fd);
		safe_close(write_fd);
	}
	return (ret);
}

int	redirect_subshell_io(t_sh *shell, t_ct *cmd_table)
{
	int		read_fd;
	int		write_fd;
	int		ret;

	read_fd = -1;
	write_fd = -1;
	ret = open_io_files(shell, &read_fd, &write_fd, cmd_table->io_red_list);
	if (ret == SUCCESS && \
		((read_fd != -1 && dup2(read_fd, STDIN_FILENO) == -1) || \
		(write_fd != -1 && dup2(write_fd, STDOUT_FILENO) == -1)))
	{
		perror(PROGRAM_NAME);
		ret = GENERAL_ERROR;
	}
	safe_close(&read_fd);
	safe_close(&write_fd);
	return (ret);
}

bool	restore_std_io(int saved_std_io[2])
{
	int	error;

	error = SUCCESS;
	if (saved_std_io[0] != -1)
		if (dup2(saved_std_io[0], STDIN_FILENO) == -1)
			error = errno;
	if (saved_std_io[1] != -1)
		if (dup2(saved_std_io[1], STDOUT_FILENO) == -1)
			error = errno;
	if (error != SUCCESS)
	{
		print_error("%s: %s\n", PROGRAM_NAME, strerror(error));
		return (false);
	}
	return (true);
}
