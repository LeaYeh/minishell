/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:15 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/18 19:43:49 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_putnbr_base_fd function writes a long integer to the given file
 * descriptor using a specified base.
 *
 * @param n    The number to write.
 * @param base The base to use for the number representation.
 * @param fd   The file descriptor to write to.
 *
 * @return It always returns the number of characters written.
 */

#include "libft.h"

static size_t	baselen(const char *base);
static int		check_for_duplicate(const char *base, size_t len);
static int		print(unsigned long u_n, const char *base, size_t len, int fd);

int	ft_putnbr_base_fd(long n, const char *base, int fd)
{
	size_t			len;
	unsigned long	u_n;
	int				written;

	if (base == NULL || fd < 0)
		return (0);
	len = baselen(base);
	if (len < 2 || check_for_duplicate(base, len))
		return (0);
	written = 0;
	if (n < 0)
	{
		if (write(fd, "-", 1) == 1)
			written += 1;
		u_n = (unsigned long) n * -1;
	}
	else
		u_n = (unsigned long) n;
	written += print(u_n, base, len, fd);
	return (written);
}

static size_t	baselen(const char *base)
{
	size_t	len;

	len = 0;
	while (base[len])
	{
		if (base[len] == '+' || base[len] == '-')
			return (0);
		len++;
	}
	return (len);
}

static int	check_for_duplicate(const char *base, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	print(unsigned long u_n, const char *base, size_t len, int fd)
{
	int	written;

	written = 0;
	if (u_n >= len)
		written += print(u_n / len, base, len, fd);
	u_n %= len;
	if (write(fd, &base[u_n], 1) == 1)
		written += 1;
	return (written);
}
