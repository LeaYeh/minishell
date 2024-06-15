/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:22 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/20 19:17:01 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strtok function checks if the string s contains digits ONLY.
 *
 * @param s    The string to check.
 *
 * @return     Returns 1 if the string s containts digits only, otherwise 0.
 *
 */
int	ft_strisdigits(const char *s)
{
	const unsigned char	*casted_ptr_s;

	if (s == NULL)
		return (0);
	casted_ptr_s = (const unsigned char *) s;
	while (ft_isdigit(*casted_ptr_s))
		casted_ptr_s++;
	if (*casted_ptr_s == '\0')
		return (1);
	else
		return (0);
}
