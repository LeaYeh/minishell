/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easter_egg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:54:08 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/02 23:07:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

int	exec_easter_egg(void)
{
	static int	egg_counter;

	if (egg_counter % 2 == 0 && WELCOME_ART1)
		printf(WELCOME_ART1);
	else if (WELCOME_ART2)
		printf(WELCOME_ART2);
	else
		printf(WELCOME_MSG);
	if (WELCOME_ART1 || WELCOME_ART2)
		printf(VALERIA_MSG);
	egg_counter++;
	return (42);
}
