/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 01:01:07 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/18 14:08:42 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

size_t	get_offset(char *str)
{
	size_t	offset;

	offset = 0;
	if (*str == '$')
	{
		offset++;
		str++;
	}
	if (*str == OPENING_BRACE)
		offset++;
	return (offset);
}

size_t	get_replace_len(char *str)
{
	size_t	replace_len;

	replace_len = 0;
	if (str[replace_len] == '$')
		replace_len++;
	if (str[replace_len] == OPENING_BRACE)
	{
		if (skip_dollar_brace(str, &replace_len, is_open_pair('"', OP_GET)))
			replace_len++;
	}
	else if (str[replace_len] == '?')
		replace_len++;
	else
		while (is_valid_varname_char(str[replace_len]))
			replace_len++;
	return (replace_len);
}

void	skip_to_dollar_not_in_single_quotes(char *str, size_t *i)
{
	while (str[*i])
	{
		if (str[*i] == '$')
			return ;
		else if (str[*i] == '"')
			is_open_pair('"', OP_SET);
		else if (str[*i] == '\'' && !is_open_pair('"', OP_GET))
			skip_single_quote(str, i);
		(*i)++;
	}
}

void	skip_to_expander_symbol(char *str, size_t *i)
{
	while (str[*i])
	{
		if (ft_strchr(EXPANDER_SYMBOLS, str[*i]))
			return ;
		(*i)++;
	}
}
