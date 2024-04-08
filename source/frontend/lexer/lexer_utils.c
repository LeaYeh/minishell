/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:33:59 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/08 12:41:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	is_operator(char *token_data)
{
	if (ft_strncmp(token_data, "&&", 2) == 0 || \
		ft_strncmp(token_data, "|", 1) == 0 || \
		ft_strncmp(token_data, "<", 1) == 0 || \
		ft_strncmp(token_data, ">", 1) == 0 || \
		ft_strncmp(token_data, "(", 1) == 0 || \
		ft_strncmp(token_data, ")", 1) == 0)
		return (true);
	return (false);
}

void	print_missing_pair_error(char *str)
{
	char	missing_pair;

	if (ft_strncmp(str, DOLLAR_BRACE, 2) == 0)
		missing_pair = CLOSING_BRACE;
	else
		missing_pair = *str;
	ft_dprintf(STDERR_FILENO, ERROR_LEXER_SYNTAX, PROGRAM_NAME, missing_pair);
}

void	skip_operator(char *token_data, int *i)
{
	if (token_data[*i] == '<' || token_data[*i] == '>' || \
		token_data[*i] == '|' || token_data[*i] == '&')
	{
		(*i)++;
		if (token_data[*i] == token_data[*i - 1])
			(*i)++;
	}
	else if (token_data[*i] == '(' || token_data[*i] == ')')
		(*i)++;
}

bool	split_token_node(t_list *node_front, int i)
{
	t_tok	*new_token;
	t_list	*node_back;
	char	*token_data_node_back;
	char	**token_data_node_front;
	char	**token_data_split;

	token_data_node_front = &((t_tok *)node_front->content)->data;
	token_data_split = ft_split_at_index(*token_data_node_front, i);
	if (!token_data_split)
		return (false);
	free(*token_data_node_front);
	*token_data_node_front = token_data_split[0];
	token_data_node_back = token_data_split[1];
	free(token_data_split);
	new_token = init_token(T_NONE, token_data_node_back);
	if (!new_token)
		return (free(token_data_node_back), false);
	node_back = ft_lstnew(new_token);
	if (!node_back)
		return (free_token(new_token), false);
	ft_lstinsert_after(&node_front, node_back);
	return (true);
}
