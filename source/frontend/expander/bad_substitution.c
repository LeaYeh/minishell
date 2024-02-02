/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:58:09 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/18 19:11:23 by ldulling         ###   ########.fr       */
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

void	prepare_error_msg(char *str, size_t *i)
{
	char	*occurrence;

	if (is_open_pair('"', OP_GET))
	{
		occurrence = ft_strchr(&str[*i], '"');
		if (occurrence)
			*occurrence = '\0';
		while (str[*i - 1] != '"')
			(*i)--;
	}
	else
		*i = 0;
}

bool	is_bad_substitution(char *str, t_expander_op op_mask)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (op_mask & ~E_HEREDOC)
			skip_to_dollar_not_in_single_quotes(str, &i);
		if (!str[i])
			break ;
		i++;
		if (!check_braces(str, &i))
		{
			prepare_error_msg(str, &i);	// Not sure about interaction with heredoc yet.
			ft_dprintf(STDERR_FILENO, ERROR_EXPANDER_BAD_SUBSTITUTION,
				PROGRAM_NAME, &str[i]);
			is_open_pair('"', OP_RESET);
			return (true);
		}
	}
	is_open_pair('"', OP_RESET);
	return (false);
}
