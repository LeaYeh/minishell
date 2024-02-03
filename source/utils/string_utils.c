/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:50:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/03 14:28:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	replace_string_content(char **str, char *new_content)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strdup(new_content);
	if (!*str)
		return (free(tmp), false);
	return (free(tmp), true);
}

bool	is_valid_varname(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_valid_varname_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	skip_to_same_quote(char *str, size_t *i)
{
	char	*open_quote;

	open_quote = ft_strchr(QUOTES, str[*i]);
	if (!open_quote)
		return (true);
	while (str[*i])
	{
		(*i)++;
		if (str[*i] == *open_quote)
			return (true);
	}
	return (false);
}
