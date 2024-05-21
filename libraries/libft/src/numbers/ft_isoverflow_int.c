/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoverflow_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:39:46 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/21 15:09:39 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_isoverflow_int function checks if the passed string represents a
 * number that would cause an overflow if converted to an integer.
 *
 * The function skips any leading whitespace and checks for a sign character
 * ('+' or '-').
 * It then compares the number part of the string with the maximum positive
 * integer value (2147483647) or the maximum negative integer value
 * (-2147483648) depending on the sign.
 *
 * @param nptr    The null-terminated string to check.
 *
 * @return        Returns true if the string represents a number that would
 *                cause an overflow, false otherwise.
 *
 */
bool	ft_isoverflow_int(const char *nptr)
{
	int		i;
	char	*int_max;
	int		num_len;

	i = 0;
	while (nptr[i] && ft_strchr(WHITESPACE, nptr[i]))
		i++;
	if (nptr[i] == '-')
		int_max = "2147483648";
	else
		int_max = "2147483647";
	if (ft_issign(nptr[i]))
		i++;
	while (nptr[i] == '0')
		i++;
	num_len = 0;
	while (ft_isdigit(nptr[i + num_len]))
		num_len++;
	if (num_len > (int)ft_strlen(int_max) || \
		ft_strncmp(&nptr[i], int_max, num_len) > 0)
		return (true);
	return (false);
}
