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

size_t	count_offset(char *str)
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

size_t	count_replace_len(char *str)
{
	size_t	replace_len;

	replace_len = 0;
	if (str[replace_len] == '$')
		replace_len++;
	if (str[replace_len] == OPENING_BRACE)
	{
		skip_dollar_brace(str, &replace_len, is_open_pair('"', OP_GET));
		replace_len++;
	}
	else if (str[replace_len] == '?')
		replace_len++;
	else
		while (is_valid_varname_char(str[replace_len]))
			replace_len++;
	return (replace_len);
}

bool	is_open_pair(unsigned char c, t_is_open_pair_op operation)
{
	static bool	is_open_pair[UCHAR_MAX];

	if (operation == OP_GET)
		return (is_open_pair[c]);
	else if (operation == OP_TOGGLE)
		is_open_pair[c] ^= true;
	else if (operation == OP_RESET)
		is_open_pair[c] = false;
	else if (operation == OP_CLEAN)
		while (c < UCHAR_MAX)
			is_open_pair[c++] = false;
	return (is_open_pair[c]);
}

void	skip_to_dollar(char *str, size_t *i)
{
	while (str[*i])
	{
		if (str[*i] == '$')
			return ;
		(*i)++;
	}
}

void	skip_to_dollar_not_in_single_quotes(char *str, size_t *i)
{
	while (str[*i])
	{
		if (str[*i] == '$')
			return ;
		else if (str[*i] == '"')
			is_open_pair('"', OP_TOGGLE);
		else if (str[*i] == '\'' && !is_open_pair('"', OP_GET))
			if (!skip_to_same_quote(str, i))
				return ;
		(*i)++;
	}
}
