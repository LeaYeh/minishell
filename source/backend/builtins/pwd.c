/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:16 by lyeh              #+#    #+#             */
/*   Updated: 2025/05/12 20:25:18 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	exec_pwd(t_sh *shell)
{
	shell->builtin_allocation = getcwd(NULL, 0);
	if (!shell->builtin_allocation)
	{
		print_error("%s: %s: %s\n", PROGRAM_NAME, "pwd", strerror(errno));
		if (errno == ENOMEM)
			return (MALLOC_ERROR);
		else
			return (GENERAL_ERROR);
	}
	ft_printf("%s\n", shell->builtin_allocation);
	ft_free_and_null(&shell->builtin_allocation);
	return (EXIT_SUCCESS);
}
