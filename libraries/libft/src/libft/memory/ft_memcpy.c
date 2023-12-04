/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:08:20 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/04 11:49:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_memcpy function copies n bytes from memory area src to memory area
 * dest.
 * The memory areas must not overlap.
 *
 * @param dest  The memory area to copy to.
 * @param src   The memory area to copy from.
 * @param n     The number of bytes to copy.
 *              Note: Giving dest or src as NULL with n not 0 will cause a
 *              segmentation fault.
 *
 * @return Returns a pointer to dest.
 *
 */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*casted_ptr_dest;
	unsigned char	*casted_ptr_src;
	size_t			i;

	if (n)
	{
		casted_ptr_dest = (unsigned char *) dest;
		casted_ptr_src = (unsigned char *) src;
		i = 0;
		while (i < n)
		{
			casted_ptr_dest[i] = casted_ptr_src[i];
			i++;
		}
	}
	return (dest);
}
