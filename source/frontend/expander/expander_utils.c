/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 01:01:07 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/06 00:21:46 by ldulling         ###   ########.fr       */
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
		while (str[++replace_len] != CLOSING_BRACE)
			;
		replace_len++;
	}
	else if (str[replace_len] == '?')
		replace_len++;
	else
		while (is_valid_varname(str[replace_len]))
			replace_len++;
	return (replace_len);
}

void	free_and_reset(char *dup, char **str)
{
	free(dup);
	ft_free_and_null((void **)str);
	is_open_pair('"', RESET);
}

bool	is_open_pair(unsigned char c, int operation)
{
	static bool	is_open_pair[UCHAR_MAX];

	if (operation == TOGGLE)
		is_open_pair[c] ^= true;
	else if (operation == RESET)
		is_open_pair[c] = false;
	return (is_open_pair[c]);
}

void	skip_to_dollar_not_in_single_quotes(char *str, size_t *i)
{
	while (str[*i])
	{
		if (str[*i] == '$')
			return ;
		else if (str[*i] == '"')
			is_open_pair('"', TOGGLE);
		else if (str[*i] == '\'' && !is_open_pair('"', GET))
			if (!skip_to_same_quote(str, i))
				return ;
		(*i)++;
	}
}
