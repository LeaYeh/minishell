/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:33:59 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/20 11:34:52 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

void	skip_operator(char *data, size_t *i)
{
	if (data[*i] == '<' || data[*i] == '>' || \
		data[*i] == '|' || data[*i] == '&')
	{
		(*i)++;
		if (data[*i] == data[*i - 1])
			(*i)++;
	}
	else if (data[*i] == '(' || data[*i] == ')')
		(*i)++;
}

void	skip_past_same_quote(char *str, size_t *i)
{
	char	*open_quote;

	open_quote = ft_strchr(QUOTES, str[*i]);
	if (open_quote)
	{
		while (str[*i])
		{
			(*i)++;
			if (str[*i] == *open_quote)
			{
				(*i)++;
				break ;
			}
		}
	}
}

bool	split_node(t_list *lst_node1, size_t i)
{
	char	**data_node1;
	char	**data_split;
	t_list	*lst_node2;
	t_token	*new_token;

	data_node1 = &((t_token *) lst_node1->content)->data;
	data_split = ft_split_at_index(*data_node1, i);
	if (!data_split)
		return (false);
	free(*data_node1);
	*data_node1 = data_split[0];
	new_token = init_token_node(T_UNINITIALIZED, data_split[1]);
	if (!new_token)
		return (free(data_split[1]), free(data_split), false);
	lst_node2 = ft_lstnew(new_token);
	if (!lst_node2)
		return (free_token_node(new_token), free(data_split), (false));
	ft_lstinsert_after(&lst_node1, lst_node2);
	free(data_split);
	return (true);
}
