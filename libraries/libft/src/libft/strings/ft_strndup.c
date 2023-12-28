/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:14:59 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/28 20:20:53 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strndup function duplicates up to n characters of the string pointed
 * to by s.
 * If s is longer than n, only n characters are copied, and a terminating null
 * byte ('\0') is added.
 * If n is greater than the length of s, the returned string will be an exact
 * duplicate of the string pointed to by s.
 * If n is 0, an empty string will be returned.
 *
 * @param s    A pointer to the string to be duplicated.
 * @param n    The maximum number of characters to be duplicated from s.
 *
 * @return     A pointer to the newly allocated string, or NULL if the
 *             allocation failed.
 *             The returned string will have to be freed later.
 *
 * @note       Calling ft_strndup with s equal to NULL with n not 0 will cause a
 *             segmentation fault (mirrors the behavior of the original
 *             strndup).
 *
 */
char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	if (n == 0)
		return (ft_strdup(""));
	len = ft_strlen(s) + 1;
	if (n > len)
		n = len;
	dup = (char *) malloc((n + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	dup = ft_memcpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}
