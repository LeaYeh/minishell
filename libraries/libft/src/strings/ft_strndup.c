/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:14:59 by ldulling          #+#    #+#             */
/*   Updated: 2024/02/15 12:31:46 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strndup function duplicates up to n characters from the string pointed
 * to by s. If s is longer than n, only n characters are copied, and a
 * NUL-terminator is added.
 *
 * @param s    A pointer to the string to be duplicated.
 * @param n    The maximum number of characters to be duplicated.
 *
 * @return     A pointer to the newly allocated string, or NULL if the
 *             allocation failed.
 *             The returned string will have to be freed later.
 *
 * @note       Calling ft_strdup with s equal to NULL with a size not 0 will
 *             cause a segmentation fault (mirrors the behavior of the original
 *             strdup).
 *
 */
char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	if (s == NULL && n == 0)
		return (ft_strdup(""));
	len = ft_strlen(s);
	if (len > n)
		len = n;
	dup = (char *) malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	dup = ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}
