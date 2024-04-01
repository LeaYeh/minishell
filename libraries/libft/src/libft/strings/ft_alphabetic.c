/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alphabetic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:41:28 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/01 18:35:35 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	compare_case_insensitive(const char *str1, const char *str2);
static int	compare_case_sensitive(const char *str1, const char *str2);
static int	compare_non_alphanumeric(const char *str1, const char *str2);

/**
 * The ft_alphabetic function compares two strings for the following order:
 * 1. Numeric characters come before alphabetic characters.
 * 2. Alphabetic characters are compared ignoring case.
 * 3. Lowercase characters come before uppercase characters.
 * 4. If equal alphanumerically, non-alphanumeric characters are given priority.
 * 5. If both are non-alphanumeric, lower ASCII value comes first.
 *
 * @param str1    The first string to be compared.
 * @param str2    The second string to be compared.
 *
 * @return        True, if str1 should come before str2, false otherwise.
 *
 */
bool	ft_alphabetic(const char *str1, const char *str2)
{
	int	diff;

	diff = compare_case_insensitive(str1, str2);
	if (diff)
		return (diff < 0);
	diff = compare_case_sensitive(str1, str2);
	if (diff)
		return (diff < 0);
	diff = compare_non_alphanumeric(str1, str2);
	if (diff)
		return (diff < 0);
	return (ft_strcmp(str1, str2) <= 0);
}

static int	compare_case_insensitive(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (ft_isalnum(*str1) && ft_isalnum(*str2))
		{
			if (ft_tolower(*str1) != ft_tolower(*str2))
				return (ft_tolower(*str1) - ft_tolower(*str2));
			str1++;
			str2++;
		}
		while (!ft_isalnum(*str1) && *str1)
			str1++;
		while (!ft_isalnum(*str2) && *str2)
			str2++;
	}
	return (*str1 - *str2);
}

static int	compare_case_sensitive(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (ft_isalnum(*str1) && ft_isalnum(*str2))
		{
			if (ft_tolower(*str1) == ft_tolower(*str2) && *str1 != *str2)
				return (*str2 - *str1);
			str1++;
			str2++;
		}
		while (!ft_isalnum(*str1) && *str1)
			str1++;
		while (!ft_isalnum(*str2) && *str2)
			str2++;
	}
	return (*str1 - *str2);
}

static int	compare_non_alphanumeric(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (!ft_isalnum(*str1) && ft_isalnum(*str2))
			return (-1);
		if (ft_isalnum(*str1) && !ft_isalnum(*str2))
			return (1);
		if (!ft_isalnum(*str1) && !ft_isalnum(*str2) && *str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
