/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrplc_part.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:19:37 by ldulling          #+#    #+#             */
/*   Updated: 2024/02/15 02:50:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_front_and_rplcmt(const char *str, const char *rplcmt, \
									size_t start);
static char	*join_new_and_back(char *str_new, const char *str, size_t end);

/**
 * The ft_strrplc_part function replaces a part of a string with a replacement
 * string.
 *
 * @param str       The address of the string to modify.
 *                  If str is NULL or points to NULL, the function does nothing.
 * @param rplcmt    The string to replace the part with.
 *                  If rplcmt is NULL, the function does nothing.
 * @param start     The index in the string where the replacement should start.
 * @param len       The length of the part to replace.
 *
 * @return          If the replacement is successful, the function returns true.
 *                  If str is NULL or points to NULL, or rplcmt is NULL, the
 *                  function also returns true.
 *                  If an error occurs, the function returns false.
 *
 */
bool	ft_strrplc_part(char **str, const char *rplcmt, size_t start, \
						size_t len)
{
	size_t	end;
	char	*str_new;

	if (!str || !*str || !rplcmt)
		return (true);
	if (start > 0)
		str_new = join_front_and_rplcmt(*str, rplcmt, start);
	else
		str_new = ft_strdup(rplcmt);
	if (!str_new)
		return (false);
	end = start + len;
	if (end < ft_strlen(*str))
	{
		str_new = join_new_and_back(str_new, *str, end);
		if (!str_new)
			return (false);
	}
	free(*str);
	*str = str_new;
	return (true);
}

static char	*join_front_and_rplcmt(const char *str, const char *rplcmt,
									size_t start)
{
	char	*str_front;
	char	*str_joined;

	str_front = ft_substr(str, 0, start);
	if (!str_front)
		return (NULL);
	str_joined = ft_strjoin(str_front, rplcmt);
	return (free(str_front), str_joined);
}

static char	*join_new_and_back(char *str_new, const char *str, size_t end)
{
	char	*str_joined;

	str_joined = ft_strjoin(str_new, &str[end]);
	return (free(str_new), str_joined);
}
