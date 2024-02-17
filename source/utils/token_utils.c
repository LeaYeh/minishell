/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:01:28 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/30 15:00:57 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

t_token	*init_token_node(int type, char *data)
{
	t_token	*token_node;

	token_node = (t_token *)malloc(sizeof(t_token));
	if (!token_node)
		return (NULL);
	token_node->type = type;
	token_node->data = data;
	return (token_node);
}

void	free_token_node(t_token *token)
{
	if (!token)
		return ;
	free(token->data);
	free(token);
}

t_token	*dup_token_node(t_token *token)
{
	t_token	*dup_token;
	char	*dup_data;

	dup_data = NULL;
	if (token->data)
	{
		dup_data = ft_strdup(token->data);
		if (!dup_data)
			return (NULL);
	}
	dup_token = init_token_node(token->type, dup_data);
	if (!dup_token)
		return (free(dup_data), NULL);
	return (dup_token);
}

t_list	*dup_token_list(t_list *token_list)
{
	t_list	*dup_list;
	t_list	*node;
	t_token	*token;

	dup_list = NULL;
	while (token_list)
	{
		token = dup_token_node(token_list->content);
		if (!token)
		{
			ft_lstclear(&dup_list, (void *)free_token_node);
			return (NULL);
		}
		node = ft_lstnew(token);
		if (!node)
			return (free_token_node(token),
				ft_lstclear(&dup_list, (void *)free_token_node),
				NULL);
		ft_lstadd_back(&dup_list, node);
		token_list = token_list->next;
	}
	return (dup_list);
}
