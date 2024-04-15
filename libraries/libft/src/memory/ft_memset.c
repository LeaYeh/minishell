/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:11:59 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/24 16:22:21 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	casted_c;
	unsigned char	*casted_ptr_s;
	size_t			i;

	casted_ptr_s = (unsigned char *) s;
	casted_c = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		casted_ptr_s[i] = casted_c;
		i++;
	}
	return (s);
}
