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

int	get_offset(char *str)
{
	int	offset;

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

int	get_replace_len(char *str)
{
	int	replace_len;

	replace_len = 0;
	if (str[replace_len] == '$')
	{
		replace_len++;
		if (str[replace_len] == OPENING_BRACE)
		{
			if (skip_dollar_brace(str, &replace_len, is_open_pair('"', OP_GET)))
				replace_len++;
		}
		else if (str[replace_len] == '?' || str[replace_len] == '$')
			replace_len++;
		else
			while (is_valid_varname_char(str[replace_len]))
				replace_len++;
	}
	else if (str[replace_len] == '*')
		while (str[replace_len] == '*')
			replace_len++;
	return (replace_len);
}

bool	is_unquoted_quote(char quote)
{
	if (quote == '"' && !is_open_pair('\'', OP_GET))
		return (true);
	if (quote == '\'' && !is_open_pair('"', OP_GET))
		return (true);
	return (false);
}

void	skip_to_dollar_not_in_single_quotes(char *str, int *i)
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
