/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 00:34:37 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/18 14:18:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

bool	parameter_expansion(char **str, t_shell *shell)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		skip_to_dollar_not_in_single_quotes(*str, &i);
		if (!(*str)[i])
			break ;
		if (!expand_parameter(str, &i, shell))
			return (is_open_pair('"', RESET), false);
	}
	is_open_pair('"', RESET);
	return (true);
}

bool	expand_parameter(char **str, size_t *i, t_shell *shell)
{
	size_t	offset;

	offset = count_offset(&(*str)[*i]);
	if ((*str)[*i + offset])
	{
		if ((*str)[*i + offset] == '?')
			return (expand_exit_code(str, i, shell->exit_code));
		else if (is_valid_varname_start((*str)[*i + offset]))
			return (expand_variable(str, i, offset, shell->env_list));
		else if (ft_strchr(QUOTES, (*str)[*i + offset]))
			return (handle_dollar_quotes(str, i));
		*i += offset;
	}
	(*i)++;
	return (true);
}

// Currently removes the dollar sign for this test case: $"$$$$'
// It better shouldn't.
// TODO We have have to check for unclosed quotes somewhere
bool	handle_dollar_quotes(char **str, size_t *i)
{
	if (!is_open_pair('"', GET))
		return (replace_part_of_str(str, "", *i, 1));
	else
		(*i)++;
	return (true);
}
