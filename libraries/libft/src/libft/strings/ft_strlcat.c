/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:15:16 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/04 12:31:10 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_strlcat function appends the NUL-terminated string src to the end of
 * dst.
 * It will append at most size - strlen(dst) - 1 characters.
 * It will then NUL-terminate, unless size is 0 or the original dst string was
 * longer than size.
 *
 * @param dst   The string to be appended to.
 *              Note: Giving dst as NULL with a size not 0 will cause a
 *              segmentation fault.
 * @param src   The string to append to dst.
 *              Note: Giving src as NULL will cause a segmentation fault.
 * @param size  The total size of dst, including the space for the
 *              NUL-terminator.
 *
 * @return The total length of the string it tried to create, that means the
 *         initial length of dst plus the length of src.
 *         If the return value is >= size, the output string has been truncated.
 */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	catlen;
	size_t	dstlen;
	size_t	srclen;

	if (dst == NULL && size == 0 && src)
		return (0);
	dstlen = ft_strlen(dst);
	catlen = dstlen;
	srclen = 0;
	while (catlen + 1 < size && src[srclen])
	{
		dst[catlen] = src[srclen];
		catlen++;
		srclen++;
	}
	if (dstlen < size)
		dst[catlen] = '\0';
	while (src[srclen])
		srclen++;
	if (size < dstlen)
		return (size + srclen);
	else
		return (dstlen + srclen);
}
