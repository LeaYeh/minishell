/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:15:16 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/25 17:15:46 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	catlen;
	size_t	dstlen;
	size_t	srclen;

	if (dst == NULL && size == 0)
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
