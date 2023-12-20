/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:04 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/20 19:15:03 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_putnchar_fd function writes a character n times to the given file
 * descriptor.
 *
 * @param c     The character to write.
 * @param n     The number of times to write the character.
 * @param fd    The file descriptor to write to.
 *
 * @return      It always returns the number of characters written.
 *
 */
size_t	ft_putnchar_fd(unsigned char c, size_t n, int fd)
{
	size_t	written;

	written = 0;
	if (fd < 0)
		return (0);
	while (n > 0)
	{
		if (write(fd, &c, 1) == 1)
			written += 1;
		n--;
	}
	return (written);
}
