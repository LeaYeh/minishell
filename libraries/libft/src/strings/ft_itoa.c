/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:05 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/24 16:20:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n);
static void	convert(long n, char *s, int char_count);

char	*ft_itoa(int n)
{
	char	*s;
	int		char_count;

	char_count = count_digits(n);
	if (n < 0)
		char_count++;
	s = (char *) malloc((char_count + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	convert(n, s, char_count);
	return (s);
}

static int	count_digits(int n)
{
	int	char_count;

	char_count = 0;
	if (n == 0)
		char_count = 1;
	else
	{
		while (n != 0)
		{
			n /= 10;
			char_count++;
		}
	}
	return (char_count);
}

static void	convert(long n, char *s, int char_count)
{
	s[char_count] = '\0';
	char_count--;
	if (n == 0)
		s[0] = '0';
	else
	{
		if (n < 0)
		{
			s[0] = '-';
			n *= -1;
		}
		while (n > 0)
		{
			s[char_count] = n % 10 + '0';
			char_count--;
			n /= 10;
		}
	}
	return ;
}
