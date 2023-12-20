/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:54:32 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/20 12:05:34 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "utils.h"

bool	create_token_list(t_list **token_list, t_list **data_list)
{
	t_list	*new_nodes;
	t_token	*token;

	new_nodes = NULL;
	while (*data_list)
	{
		token = init_token_node(T_UNINITIALIZED, (*data_list)->content);
		if (!token)
			break ;
		new_nodes = ft_lstnew(token);
		if (!new_nodes || !separate_operators(new_nodes, 0))
			break ;
		get_type(new_nodes);
		ft_lstadd_back(token_list, new_nodes);
		free(ft_lstpop(data_list));
	}
	if (*data_list)
		return (ft_lstclear(data_list, free), free_token_node(token), \
				ft_lstclear(&new_nodes, free), false);
	return (true);
}

bool	separate_operators(t_list *lst_node, size_t i)
{
	char	*data;

	data = ((t_token *) lst_node->content)->data;
	while (data[i])
	{
		if (ft_strchr(TOK_SYMBOLS, data[i]))
		{
			if (i == 0)
				skip_operator(data, &i);
			if (data[i])
			{
				if (!split_node(lst_node, i))
					return (false);
				lst_node = lst_node->next;
				data = ((t_token *) lst_node->content)->data;
				i = 0;
			}
		}
		else if (ft_strchr(QUOTES, data[i]))
			skip_past_same_quote(data, &i);
		else
			i++;
	}
	return (true);
}

bool	add_end_node(t_list	**token_list)
{
	t_list	*new_node;
	t_token	*token;

	token = init_token_node(T_END, NULL);
	if (!token)
		return (false);
	new_node = (ft_lstnew(token));
	if (!new_node)
		return (free(token), false);
	ft_lstadd_back(token_list, new_node);
	return (true);
}
