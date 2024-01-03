/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 01:01:07 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/03 01:42:15 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	free_and_reset(char *dup)
{
	free(dup);
	is_open_pair('"', RESET);
}

bool	is_open_pair(unsigned char c, int operation)
{
	static bool	is_open_pair[UCHAR_MAX];

	if (operation == TOGGLE)
		is_open_pair[c] ^= true;
	else if (operation == RESET)
		is_open_pair[c] = false;
	return (is_open_pair[c]);
}
