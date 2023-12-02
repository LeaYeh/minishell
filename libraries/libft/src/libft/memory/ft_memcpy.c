/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:08:20 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/25 15:51:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*casted_ptr_dest;
	unsigned char	*casted_ptr_src;
	size_t			i;

	if (dest || src)
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
