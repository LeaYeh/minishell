/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:30 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/18 19:37:34 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_putnstr_fd function writes up to n characters of a string to the given
 * file descriptor.
 *
 * @param str The string to write.
 * @param n   The maximum number of characters to write.
 * @param fd  The file descriptor to write to.
 *
 * @return It always returns the number of characters written.
 */

#include "libft.h"

size_t	ft_putnstr_fd(const char *s, size_t n, int fd)
{
	size_t	len;
	ssize_t	written;

	written = 0;
	if (s == NULL || n == 0 || fd < 0)
		return (0);
	len = ft_strlen(s);
	if (len > n)
		len = n;
	written += write(fd, s, len);
	if (written < 0)
		written = 0;
	return ((size_t) written);
}
