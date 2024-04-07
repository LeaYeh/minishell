/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_data_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:30:35 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/21 17:36:36 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static bool	set_token_data(char **token_data, char *input_line, int *i);

bool	create_token_data_list(t_list **token_data_list, char *input_line)
{
	int		i;
	char	*token_data;

	i = 0;
	while (input_line[i])
	{
		while (ft_strchr(WHITESPACE, input_line[i]) && input_line[i])
			i++;
		if (!input_line[i])
			break ;
		if (!set_token_data(&token_data, input_line, &i))
			return (false);
		if (!token_data)
			return (ft_lstclear(token_data_list, free), true);
		if (!ft_lstnew_back(token_data_list, token_data))
			return (free(token_data), false);
	}
	return (true);
}

static bool	set_token_data(char **token_data, char *input_line, int *i)
{
	bool	is_missing_pair;
	int		start;

	start = *i;
	is_missing_pair = false;
	while (input_line[*i] && !is_missing_pair && \
		!ft_strchr(WHITESPACE, input_line[*i]))
	{
		if (input_line[*i] == '\'')
			is_missing_pair = !skip_single_quote(input_line, i);
		else if (input_line[*i] == '"')
			is_missing_pair = !skip_double_quote(input_line, i);
		else if (ft_strncmp(&input_line[*i], DOLLAR_BRACE, 2) == 0)
			is_missing_pair = !skip_dollar_brace(input_line, i, false);
		if (!is_missing_pair)
			(*i)++;
	}
	if (is_missing_pair)
		return (print_missing_pair_error(&input_line[*i]),
			*token_data = NULL, true);
	*token_data = ft_substr(input_line, start, *i - start);
	if (!*token_data)
		return (false);
	return (true);
}
