/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:08:23 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/13 21:32:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks if dest is before or after src in memory, then starts copying from
 * the beginning or the end respectively.
 */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*casted_ptr_dest;
	unsigned char	*casted_ptr_src;
	size_t			i;

	if (dest || src)
	{
		casted_ptr_dest = (unsigned char *) dest;
		casted_ptr_src = (unsigned char *) src;
		if (casted_ptr_dest <= casted_ptr_src)
		{
			i = 0;
			while (i < n)
			{
				casted_ptr_dest[i] = casted_ptr_src[i];
				i++;
			}
		}
		else
		{
			i = n;
			while (i-- > 0)
				casted_ptr_dest[i] = casted_ptr_src[i];
		}
	}
	return (dest);
}
