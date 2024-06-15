/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:55:40 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/21 15:08:44 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_issign function checks if the passed character is a sign character
 * ('+' or '-').
 *
 * @param c    The character to check.
 *
 * @return     Returns 1 if the character is a sign character, 0 otherwise.
 *
 */
int	ft_issign(int c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}
