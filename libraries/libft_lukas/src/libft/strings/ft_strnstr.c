/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:27 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/25 17:25:08 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	l;

	if (big == NULL && len == 0)
		return (NULL);
	b = 0;
	while (1)
	{
		l = 0;
		while (little[l] == big[b + l] && b + l < len && little[l])
			l++;
		if (!little[l])
			return ((char *) &big[b]);
		else if (!big[b + l] || b + l == len)
			return (NULL);
		else
			b++;
	}
}
