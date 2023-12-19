/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:01:28 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/19 18:43:38 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

t_token	*init_token_node(int type, char *data)
{
	t_token	*token_node;

	token_node = (t_token *) malloc(sizeof(t_token));
	if (!token_node)
		return (NULL);
	token_node->type = type;
	token_node->data = data;
	return (token_node);
}

// TODO: Change variable name "content" to ptr
void	free_token_node(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token->data)
		free(token->data);
}

int	get_token_type_from_list(t_list *token_list)
{
	return (((t_token *)token_list->content)->type);
}

char	*get_token_data_from_list(t_list *token_list)
{
	return (((t_token *)token_list->content)->data);
}
