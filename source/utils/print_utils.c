/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:49:43 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/02 23:08:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	clear_terminal_soft(void)
{
	if (isatty(STDIN_FILENO))
		printf("\e[2J\e[1;1H");
}

void	print_welcome_msg(t_shell *shell)
{
	if (shell->is_interactive)
	{
		clear_terminal_soft();
		printf(WELCOME_ART1);
		printf(WELCOME_MSG);
	}
}
