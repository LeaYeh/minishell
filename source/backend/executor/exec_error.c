/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:26:12 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/11 20:54:14 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

bool	check_executable(t_shell *shell, char *filename)
{
	if (access(filename, F_OK) != 0)
	{
		shell->exit_code = CMD_NOT_FOUND;
		if (ft_strchr(filename, '/'))
			ft_dprintf(2, ERROR_PATH_NOT_FOUND, PROGRAM_NAME, filename);
		else
			ft_dprintf(2, ERROR_CMD_NOT_FOUND, PROGRAM_NAME, filename);
		return (false);
	}
	else if (is_dir(filename))
	{
		shell->exit_code = CMD_EXEC_FAILED;
		ft_dprintf(2, "%s: %s: Is a directory\n", PROGRAM_NAME, filename);
		return (false);
	}
	else if (access(filename, X_OK) != 0)
	{
		shell->exit_code = CMD_EXEC_FAILED;
		ft_dprintf(2, "%s: %s: ", PROGRAM_NAME, filename);
		perror("");
		return (false);
	}
	return (true);
}
