/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrnstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:05:04 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/28 18:52:38 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strrnstr function locates the last occurrence of the null-terminated
 * string little in the string big, where not more than len characters are
 * searched. Characters that appear after a '\0' character are not searched.
 *
 * @param big       The string to be scanned.
 * @param little    The string to be searched within big.
 * @param len       The number of characters to be scanned in big.
 *
 * @return          If little is an empty string, a pointer to the end of big is
 *                  returned; if little occurs nowhere in big, NULL is returned;
 *                  otherwise a pointer to the first character of the last
 *                  occurrence of little is returned.
 *
 * @note            Calling ft_strrnstr with big equal to NULL with a size not
 *                  0, or with little equal to NULL will cause a segmentation
 *                  fault.
 *
 */
char	*ft_strrnstr(const char *big, const char *little, size_t len)
{
	char	*last;
	char	*tmp;

	if (big == NULL && len == 0)
		return (NULL);
	if (*little == '\0')
		return ((char *) &big[ft_strlen(big)]);
	last = NULL;
	tmp = ft_strnstr(big, little, len);
	while (tmp)
	{
		last = tmp;
		tmp = ft_strnstr(tmp + 1, little, len - (tmp - big) - 1);
	}
	return (last);
}
