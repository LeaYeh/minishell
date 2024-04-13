/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:13:27 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/04 23:31:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	get_open_pair_index(unsigned char c, t_pair_op operation);

bool	skip_single_quote(char *str, int *i)
{
	int	start;

	if (is_open_pair('\'', OP_GET))
		return (false);
	start = *i;
	while (str[(*i)++])
	{
		if (str[*i] == '\'')
			return (true);
	}
	*i = start;
	return (false);
}

bool	skip_double_quote(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[(*i)++])
	{
		if (ft_strncmp(&str[*i], DOLLAR_BRACE, 2) == 0)
		{
			if (!skip_dollar_brace(str, i, true))
				return (false);
		}
		else if (str[*i] == '"')
			return (true);
	}
	*i = start;
	return (false);
}

bool	skip_dollar_brace(char *str, int *i, bool is_in_dquote)
{
	int	start;

	start = *i;
	while (str[(*i)++])
	{
		if (str[*i] == '\'' && !is_in_dquote)
		{
			if (!skip_single_quote(str, i))
				return (false);
		}
		else if (str[*i] == '"')
		{
			if (!skip_double_quote(str, i))
				return (false);
		}
		else if (ft_strncmp(&str[*i], DOLLAR_BRACE, 2) == 0)
		{
			if (!skip_dollar_brace(str, i, is_in_dquote))
				return (false);
		}
		else if (str[*i] == CLOSING_BRACE)
			return (true);
	}
	*i = start;
	return (false);
}

bool	is_open_pair(unsigned char c, t_pair_op operation)
{
	static bool	status[2];
	int			i;

	if (c == 0 && operation == OP_GET)
		return (status[0] || status[1]);
	i = get_open_pair_index(c, operation);
	if (i == -1)
		return (false);
	if (operation == OP_GET)
		return (status[i]);
	else if (operation == OP_SET)
		status[i] ^= true;
	else if (operation == OP_RESET)
		status[i] = false;
	else if (operation == OP_CLEAN)
		ft_memset(status, false, sizeof(status));
	return (status[i]);
}

static int	get_open_pair_index(unsigned char c, t_pair_op operation)
{
	if (operation == OP_CLEAN)
		return (0);
	if (c == '\'')
		return (0);
	if (c == '"')
		return (1);
	return (-1);
}
