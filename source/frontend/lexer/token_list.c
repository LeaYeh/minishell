/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:54:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/21 17:17:46 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static bool	separate_operators(
				t_list *lst_node,
				int i);
static bool	split_and_advance_node(
				t_list **lst_node,
				char **token_data,
				int *i);

bool	create_token_list(
	t_list **token_list,
	t_list **token_data_list)
{
	t_list	*new_nodes;
	t_tok	*token;

	new_nodes = NULL;
	while (*token_data_list)
	{
		token = init_token_node(T_NONE, (*token_data_list)->content);
		if (!token)
			break ;
		(*token_data_list)->content = NULL;
		new_nodes = ft_lstnew(token);
		if (!new_nodes)
			break ;
		token = NULL;
		if (!separate_operators(new_nodes, 0))
			break ;
		ft_lstadd_back(token_list, new_nodes);
		new_nodes = NULL;
		free(ft_lstpop_front(token_data_list));
	}
	if (*token_data_list)
		return (free_token_node(token), \
				ft_lstclear(&new_nodes, (void *)free_token_node), false);
	return (true);
}

bool	append_end_node(
	t_list	**token_list)
{
	t_tok	*token;

	token = init_token_node(T_END, NULL);
	if (!token || !ft_lstnew_back(token_list, token))
		return (free_token_node(token), false);
	return (true);
}

static bool	separate_operators(
	t_list *lst_node,
	int i)
{
	char	*token_data;

	token_data = get_token_data_from_list(lst_node);
	while (token_data[i])
	{
		if (token_data[i] == '\'')
			skip_single_quote(token_data, &i);
		else if (token_data[i] == '"')
			skip_double_quote(token_data, &i);
		else if (ft_strncmp(&token_data[i], DOLLAR_BRACE, 2) == 0)
			skip_dollar_brace(token_data, &i, false);
		else if (is_operator(&token_data[i]))
		{
			if (!split_and_advance_node(&lst_node, &token_data, &i))
				return (false);
			continue ;
		}
		i++;
	}
	return (true);
}

static bool	split_and_advance_node(
	t_list **lst_node,
	char **token_data,
	int *i)
{
	if (*i == 0)
		skip_operator(*token_data, i);
	if ((*token_data)[*i])
	{
		if (!split_token_node(*lst_node, *i))
			return (false);
		*lst_node = (*lst_node)->next;
		*token_data = get_token_data_from_list(*lst_node);
		*i = 0;
	}
	return (true);
}
