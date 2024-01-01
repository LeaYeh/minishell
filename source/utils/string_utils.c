/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:50:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/01 17:32:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	is_valid_varname(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_valid_varname_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

void	skip_past_same_quote(char *str, size_t *i)
{
	char	*open_quote;

	open_quote = ft_strchr(QUOTES, str[*i]);
	if (!open_quote || !*open_quote)
		return ;
	while (str[*i])
	{
		(*i)++;
		if (str[*i] == *open_quote)
		{
			(*i)++;
			break ;
		}
	}
}
