/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sputnchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 02:17:12 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/29 05:41:19 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_sputnchar(char *str, unsigned char c, size_t n)
{
	size_t	written;

	written = 0;
	if (str == NULL)
		return (0);
	while (written < n)
	{
		ft_memmove(&str[written], &c, 1);
		written++;
	}
	return (written);
}
