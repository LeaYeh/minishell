/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:27 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/12 23:00:26 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strnstr function locates the first occurrence of the null-terminated
 * string little in the string big, where not more than len characters are
 * searched. Characters that appear after a '\0' character are not searched.
 *
 * @param big       The string to be scanned.
 * @param little    The string to be searched within big.
 * @param len       The number of characters to be scanned in big.
 *
 * @return          If little is an empty string, big is returned; if little
 *                  occurs nowhere in big, NULL is returned; otherwise a pointer
 *                  to the first character of the first occurrence of little is
 *                  returned.
 *
 * @note            Calling ft_strnstr with big equal to NULL with a size not 0,
 *                  or with little equal to NULL will cause a segmentation fault
 *                  (mirrors the behavior of the original strnstr).
 *
 */
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
