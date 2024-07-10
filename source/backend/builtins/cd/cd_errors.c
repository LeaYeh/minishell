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
		print_error("%s: cd: ", PROGRAM_NAME);
		perror(NULL);
		return (MALLOC_ERROR);
	}
	print_error("%s: cd: %s: ", PROGRAM_NAME, target_dir);
	perror(NULL);
	return (GENERAL_ERROR);
}
