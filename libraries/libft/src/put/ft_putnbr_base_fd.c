/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:15 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/29 05:49:17 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_base_len(const char *base);
static bool		check_for_duplicate(const char *base, size_t base_len);
static size_t	print(unsigned long u_n, const char *base, size_t base_len, \
						int fd);

/**
 * The ft_putnbr_base_fd function writes a long integer to the given file
 * descriptor using a specified base.
 *
 * @param n       The number to write.
 * @param base    The base to use for the number representation.
 * @param fd      The file descriptor to write to.
 *
 * @return        It always returns the number of characters written.
 *
 */
size_t	ft_putnbr_base_fd(long n, const char *base, int fd)
{
	size_t			base_len;
	unsigned long	u_n;
	size_t			written;

	if (base == NULL || fd < 0)
		return (0);
	base_len = get_base_len(base);
	if (base_len < 2 || check_for_duplicate(base, base_len))
		return (0);
	written = 0;
	if (n < 0)
	{
		if (write(fd, "-", 1) == 1)
			written += 1;
		u_n = (unsigned long) -n;
	}
	else
		u_n = (unsigned long) n;
	written += print(u_n, base, base_len, fd);
	return (written);
}

static size_t	get_base_len(const char *base)
{
	size_t	base_len;

	base_len = 0;
	while (base[base_len])
	{
		if (base[base_len] == '+' || base[base_len] == '-')
			return (0);
		base_len++;
	}
	return (base_len);
}

static bool	check_for_duplicate(const char *base, size_t base_len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < base_len - 1)
	{
		j = i + 1;
		while (j < base_len)
		{
			if (base[i] == base[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

static size_t	print(unsigned long u_n, const char *base, size_t base_len, \
						int fd)
{
	size_t	written;

	written = 0;
	if (u_n >= base_len)
		written += print(u_n / base_len, base, base_len, fd);
	u_n %= base_len;
	if (write(fd, &base[u_n], 1) == 1)
		written += 1;
	return (written);
}
