/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatches_any.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:50:45 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/23 18:12:21 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	search_null_str(va_list ap, int n);

/**
 * The ft_strmatches_any function checks if the first string matches any of the
 * n other strings provided as arguments.
 *
 * @param str    The string to compare against.
 *               If str is NULL, NULL will be searched.
 * @param n      The number of strings to compare.
 * @param ...    Variable number of strings to compare with str.
 *
 * @return       If a match is found, the position of the matching string
 *               (1-indexed).
 *               If no match is found, 0.
 *
 */
int	ft_strmatches_any(const char *str, int n, ...)
{
	va_list		ap;
	int			i;
	const char	*cmp;

	va_start(ap, n);
	if (str == NULL)
		i = search_null_str(ap, n);
	else
	{
		i = 0;
		while (i < n)
		{
			cmp = va_arg(ap, const char *);
			if (cmp != NULL && ft_strcmp(str, cmp) == 0)
				break ;
			i++;
		}
	}
	va_end(ap);
	if (i == n)
		return (0);
	return (i + 1);
}

static int	search_null_str(va_list ap, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (va_arg(ap, const char *) == NULL)
			break ;
		i++;
	}
	return (i);
}
