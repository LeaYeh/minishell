/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 02:15:26 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/26 02:32:52 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	handle_chdir_error(int error, char *target_dir)
{
	ft_dprintf(STDERR_FILENO, "%s: cd: %s: ", PROGRAM_NAME, target_dir);
	perror(NULL);
	if (error == EIO || error == ENOMEM)
		return (GENERAL_ERROR);
	return (MISUSE_BUILTIN);
}

int	handle_getcwd_error(int error, char *target_dir)
{
	if (error == ENOMEM)
	{
		ft_dprintf(STDERR_FILENO, "%s: cd: ", PROGRAM_NAME);
		perror(NULL);
		return (GENERAL_ERROR);
	}
	ft_dprintf(STDERR_FILENO, "%s: cd: %s: ", PROGRAM_NAME, target_dir);
	perror(NULL);
	return (MISUSE_BUILTIN);
}
