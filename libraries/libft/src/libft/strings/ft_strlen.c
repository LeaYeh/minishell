/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:06 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/20 19:30:43 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strlen function calculates the length of the string pointed to by s,
 * excluding the terminating null byte ('\0').
 *
 * @param s    The string to be measured.
 *             Note: Calling ft_strlen with s equal to NULL will cause a
 *             segmentation fault.
 *
 * @return     The length of the string s.
 *
 */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
