/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:58:09 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/03 02:15:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

bool	check_braces(char *str, size_t *i)
{
	if (str[*i] != OPENING_BRACE)
		return (true);
	(*i)++;
	if (str[*i] != '?' && !is_valid_varname_start(str[*i]))
		return (false);
	(*i)++;
	if (str[*i - 1] != '?')
		while (is_valid_varname(str[*i]))
			(*i)++;
	if (str[*i] == '?')
		while (str[*i] && str[*i] != CLOSING_BRACE)
			(*i)++;
	if (str[*i] != CLOSING_BRACE)
		return (false);
	return (true);
}

// [x] Check if inside double quotes.
// 	   [x] Nul-terminate on ending quote.
//     [x] Move i after starting quote.
void	prepare_error_msg(char *str, size_t *i)
{
	if (is_open_pair('"', GET))
	{
		*ft_strchr(&str[*i], '"') = '\0';
		while (str[*i - 1] != '"')
			(*i)--;
	}
	else
		*i = 0;
}

bool	bad_substitution(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		skip_to_dollar_not_in_single_quotes(str, &i);
		if (!str[i])
			return (false);
		i++;
		if (!check_braces(str, &i))
		{
			prepare_error_msg(str, &i);
			ft_dprintf(STDERR_FILENO, ERROR_EXPANDER_BAD_SUBSTITUTION, &str[i]);
			return (true);
		}
	}
	return (false);
}
