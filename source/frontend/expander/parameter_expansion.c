/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 00:34:37 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/28 02:12:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

bool	handle_parameter_expansion(char **str, t_list **lst, t_shell *shell, \
									t_expander_op op_mask)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		if (op_mask & ~E_HEREDOC)
			skip_to_dollar_not_in_single_quotes(*str, &i);
		if (!(*str)[i])
			break ;
		if (!expand(str, &i, shell))
			return (is_open_pair('"', OP_RESET), false);
	}
	is_open_pair('"', OP_RESET);
	if (!(*str)[0])
		ft_free_and_null((void **)str);
	if (!ft_lstnew_back(lst, *str))
		return (false);
	return (true);
}

bool	expand(char **str, size_t *i, t_shell *shell)
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
	if (!is_open_pair('"', OP_GET))
		return (ft_rplc_part_of_str(str, "", *i, 1));
	else
		(*i)++;
	return (true);
}
