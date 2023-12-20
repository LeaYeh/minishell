/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:01:28 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/19 21:13:42 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

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
	free(token);
}

int	get_token_type_from_list(t_list *token_list)
{
	if (!token_list)
		return (T_NONE);
	return (((t_token *)token_list->content)->type);
}

char	*get_token_data_from_list(t_list *token_list)
{
	return (((t_token *)token_list->content)->data);
}

void	print_token(t_token *token)
{
	printf("(type: %s, data: %s)\n",
		ft_get_token_type_str(token->type), token->data);
}

void	print_token_list(t_list *token_list)
{
	printf("-------- TOKEN LIST --------\n");
	ft_lstiter(token_list, (void *)print_token);
	printf("----------------------------\n\n");
}
