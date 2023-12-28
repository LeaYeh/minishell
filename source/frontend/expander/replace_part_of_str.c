/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_part_of_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:19:37 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/02 19:34:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	replace_part_of_str(
			char **str, char *replacement, size_t start, size_t len)
{
	size_t	end;
	char	*str_new;

	if (!str || !*str || !replacement)
		return (true);
	if (start > 0)
		str_new = join_front_and_replacement(*str, replacement, start);
	else
		str_new = ft_strdup(replacement);
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

char	*join_front_and_replacement(char *str, char *replacement, size_t start)
{
	char	*str_front;
	char	*str_joined;

	str_front = ft_substr(str, 0, start);
	if (!str_front)
		return (NULL);
	str_joined = ft_strjoin(str_front, replacement);
	return (free(str_front), str_joined);
}

char	*join_new_and_back(char *str_new, char *str, size_t end)
{
	char	*str_joined;

	str_joined = ft_strjoin(str_new, &str[end]);
	return (free(str_new), str_joined);
}
