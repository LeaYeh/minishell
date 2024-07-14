/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 02:15:26 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/28 02:59:43 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	handle_cd_error(int error, char *target_dir)
{
	if (error == ENOMEM || error == EIO)
	{
		print_error("%s: cd: %s\n", PROGRAM_NAME, strerror(error));
		return (MALLOC_ERROR);
	}
	print_error("%s: cd: %s: %s\n", PROGRAM_NAME, target_dir, strerror(error));
	return (GENERAL_ERROR);
}
