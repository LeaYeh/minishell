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

static bool	is_valid_brace_content(char *str, int *i);
static void	print_bad_substitution_error(char *str, int i);

bool	is_bad_substitution(char *str, t_expd_op op_mask)
{
	int	i;

	if (!(op_mask & E_PARAM))
		return (false);
	i = 0;
	while (str[i])
	{
		if (op_mask & E_RM_QUOTES)
			skip_to_dollar_not_in_single_quotes(str, &i);
		if (!str[i])
			break ;
		i++;
		if (!is_valid_brace_content(str, &i))
		{
			print_bad_substitution_error(str, i);
			is_open_pair('"', OP_RESET);
			return (true);
		}
	}
	is_open_pair('"', OP_RESET);
	return (false);
}

static bool	is_valid_brace_content(char *str, int *i)
{
	if (str[*i] != OPENING_BRACE)
		return (true);
	(*i)++;
	if (!(str[*i] == '?' || str[*i] == '$' || is_valid_varname_start(str[*i])))
		return (false);
	(*i)++;
	if (str[*i - 1] != '?')
		while (is_valid_varname_char(str[*i]))
			(*i)++;
	if (str[*i] == '?')
		skip_dollar_brace(str, i, is_open_pair('"', OP_GET));
	if (str[*i] != CLOSING_BRACE)
		return (false);
	return (true);
}

static void	print_bad_substitution_error(char *str, int i)
{
	char	*start;

	if (is_open_pair('"', OP_GET))
	{
		while (str[i - 1] != '"')
			i--;
		start = &str[i--];
		skip_double_quote(str, &i);
		str[i] = '\0';
	}
	else
		start = str;
	ft_dprintf(STDERR_FILENO, ERROR_EXPANDER_BAD_SUBSTITUTION,
		PROGRAM_NAME, start);
}
