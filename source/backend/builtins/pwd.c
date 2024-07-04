/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:16 by lyeh              #+#    #+#             */
/*   Updated: 2024/06/01 12:25:09 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	exec_pwd(t_sh *shell)
{
	shell->builtin_allocation = getcwd(NULL, 0);
	if (!shell->builtin_allocation)
	{
		print_error("%s: %s: ", PROGRAM_NAME, "pwd");
		perror(NULL);
		if (errno == ENOMEM)
			return (MALLOC_ERROR);
		else
			return (GENERAL_ERROR);
	}
	ft_printf("%s\n", shell->builtin_allocation);
	ft_free_and_null(&shell->builtin_allocation);
	return (EXIT_SUCCESS);
}
