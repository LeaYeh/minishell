/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:49:43 by ldulling          #+#    #+#             */
/*   Updated: 2025/01/26 22:03:44 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_welcome_msg(t_sh *shell)
{
	if (shell->is_interactive)
	{
		clear_terminal_soft();
		print_error("%s%s", WELCOME_ART1, WELCOME_MSG);
	}
}

void	clear_terminal_soft(void)
{
	if (isatty(STDIN_FILENO))
		print_error("%s", "\e[2J\e[1;1H");
}
