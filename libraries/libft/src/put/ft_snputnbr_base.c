/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snputnbr_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 02:20:16 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/29 12:05:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_base_len(const char *base);
static bool		check_for_duplicate(const char *base, size_t base_len);
unsigned long	truncate_nbr_if_needed(unsigned long nbr, size_t base_len, \
										size_t max_len);
static size_t	sprint(char *str, unsigned long u_n, const char *base, \
						size_t base_len);

size_t	ft_snputnbr_base(char *str, long n, const char *base, size_t max_len)
{
	size_t			base_len;
	unsigned long	u_n;
	size_t			written;

	if (str == NULL || base == NULL || max_len == 0)
		return (0);
	base_len = get_base_len(base);
	if (base_len < 2 || check_for_duplicate(base, base_len))
		return (0);
	written = 0;
	if (n < 0)
	{
		written += ft_sputnchar(str, '-', 1);
		if (written == max_len)
			return (written);
		max_len--;
		u_n = (unsigned long) -n;
	}
	else
		u_n = (unsigned long) n;
	u_n = truncate_nbr_if_needed(u_n, base_len, max_len);
	written += sprint(&str[written], u_n, base, base_len);
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

unsigned long	truncate_nbr_if_needed(unsigned long nbr, size_t base_len, \
										size_t max_len)
{
	size_t			nbr_len;
	unsigned long	tmp;

	if (nbr == 0 || max_len == 0)
		return (0);
	nbr_len = 0;
	tmp = nbr;
	while (tmp != 0)
	{
		nbr_len++;
		tmp /= base_len;
	}
	if (nbr_len > max_len)
	{
		while (nbr_len > max_len)
		{
			nbr_len--;
			nbr /= base_len;
		}
	}
	return (nbr);
}

static size_t	sprint(char *str, unsigned long u_n, const char *base, \
					size_t base_len)
{
	size_t	written;

	written = 0;
	if (u_n >= base_len)
		written += sprint(&str[written], u_n / base_len, base, base_len);
	u_n %= base_len;
	written += ft_sputnchar(&str[written], base[u_n], 1);
	return (written);
}
