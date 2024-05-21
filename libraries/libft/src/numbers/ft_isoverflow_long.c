/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoverflow_long.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:39:46 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/21 19:05:36 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_isoverflow_long function checks if the passed string represents a
 * number that would cause an overflow if converted to a long integer.
 *
 * The function skips any leading whitespace and checks for a sign character
 * ('+' or '-').
 * It then compares the number part of the string with the maximum positive
 * long integer value (9223372036854775807) or the maximum negative long integer
 * value (-9223372036854775808) depending on the sign.
 *
 * @param nptr    The null-terminated string to check.
 *
 * @return        Returns true if the string represents a number that would
 *                cause an overflow, false otherwise.
 *
 */
bool	ft_isoverflow_long(const char *nptr)
{
	int		i;
	char	*long_max;
	int		long_max_len;
	int		num_len;

	i = 0;
	while (nptr[i] && ft_strchr(WHITESPACE, nptr[i]))
		i++;
	if (nptr[i] == '-')
		long_max = "9223372036854775808";
	else
		long_max = "9223372036854775807";
	long_max_len = ft_strlen(long_max);
	if (ft_issign(nptr[i]))
		i++;
	while (nptr[i] == '0')
		i++;
	num_len = 0;
	while (ft_isdigit(nptr[i + num_len]))
		num_len++;
	if ((num_len == long_max_len && ft_strncmp(&nptr[i], long_max, num_len) > 0)
		|| num_len > long_max_len)
		return (true);
	return (false);
}
