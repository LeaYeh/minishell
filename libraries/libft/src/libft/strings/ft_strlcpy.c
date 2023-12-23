/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:15:57 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/23 17:15:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strlcpy function copies the NUL-terminated string from src to dst.
 * It will copy at most size - 1 characters.
 * It will then NUL-terminate, unless size is 0 or the src string is longer than
 * size.
 *
 * @param dst     The string to copy to.
 * @param src     The string to copy from.
 * @param size    The total size of dst, including the space for the
 *                NUL-terminator.
 *
 * @return        The total length of src.
 *                If the return value is >= size, the output string has been
 *                truncated.
 *
 * @note          Calling ft_strlcpy with dst equal to NULL with a size not 0,
 *                or with src equal to NULL will cause a segmentation fault
 *                (mirrors the behavior of the original strlcpy).
 *
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (size > 0)
	{
		i = 0;
		while (i < size - 1 && i < srclen)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}
