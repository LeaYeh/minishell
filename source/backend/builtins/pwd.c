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

int	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_error("%s: %s: ", PROGRAM_NAME, "pwd");
		perror(NULL);
		if (errno == ENOMEM)
			return (MALLOC_ERROR);
		else
			return (GENERAL_ERROR);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
