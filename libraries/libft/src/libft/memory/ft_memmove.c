/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:08:23 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/04 12:03:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_memmove function copies n bytes from memory area src to memory area
 * dest.
 * Unlike ft_memcpy, the memory areas may overlap.
 * This function checks if dest is before or after src in memory, then starts
 * copying from the beginning or the end respectively.
 *
 * @param dest  The memory area to copy to.
 * @param src   The memory area to copy from.
 * @param n     The number of bytes to copy.
 *
 * @return Returns a pointer to dest.
 *         Note: Giving dest or src as NULL with n not 0 will cause a
 *         segmentation fault.
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
