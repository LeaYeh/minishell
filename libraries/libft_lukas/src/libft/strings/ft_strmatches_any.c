/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatches_any.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:50:45 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/14 09:33:58 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_strmatches_any function checks if the first string matches any of the
 * n other strings provided as arguments.
 *
 * @param str The string to compare.
 * @param n   The number of strings to compare against.
 * @param ... Variable number of strings to compare with str.
 *
 * @return If a match is found, it returns the position of the matching string
 *         (1-indexed).
 *         If no match is found, it returns 0.
 */

#include "libft.h"

int	ft_strmatches_any(const char *str, int n, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, n);
	i = 0;
	while (i++ < n)
	{
		if (ft_strcmp(str, va_arg(ap, const char *)) == 0)
		{
			va_end(ap);
			return (i);
		}
	}
	va_end(ap);
	return (0);
}
