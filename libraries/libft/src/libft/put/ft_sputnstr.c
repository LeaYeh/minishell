/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sputnstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 02:17:48 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/29 05:41:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_sputnstr(char *str, const char *s, size_t n)
{
	size_t	written;

	if (str == NULL || s == NULL || n == 0)
		return (0);
	written = ft_strlen(s) + 1;
	if (written > n)
		written = n;
	ft_memmove(str, s, written);
	return (written);
}
