/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:49:43 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/04 22:35:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_welcome_msg(t_sh *shell)
{
	if (shell->is_interactive)
	{
		clear_terminal_soft();
		ft_printf("%s", WELCOME_ART1);
		ft_printf("%s", WELCOME_MSG);
	}
}

void	clear_terminal_soft(void)
{
	if (isatty(STDIN_FILENO))
		ft_printf("%s", "\e[2J\e[1;1H");
}
