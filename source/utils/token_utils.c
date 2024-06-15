/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:01:28 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/08 12:27:27 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_tok	*dup_token(t_tok *token);

t_tok	*init_token(t_tok_typ type, char *data)
{
	t_tok	*token;

	token = (t_tok *)malloc(sizeof(t_tok));
	if (!token)
		return (NULL);
	token->type = type;
	token->data = data;
	return (token);
}

void	free_token(t_tok *token)
{
	if (!token)
		return ;
	ft_free_and_null((void **)&token->data);
	free(token);
}

t_list	*dup_token_list(t_list *token_list)
{
	t_list	*dup_list;
	t_tok	*token;

	dup_list = NULL;
	while (token_list)
	{
		token = dup_token(token_list->content);
		if (!token || !ft_lstnew_back(&dup_list, token))
		{
			free_token(token);
			ft_lstclear(&dup_list, (void *)free_token);
			return (NULL);
		}
		token_list = token_list->next;
	}
	return (dup_list);
}

static t_tok	*dup_token(t_tok *token)
{
	t_tok	*dup_token;
	char	*dup_data;

	dup_data = NULL;
	if (token->data)
	{
		dup_data = ft_strdup(token->data);
		if (!dup_data)
			return (NULL);
	}
	dup_token = init_token(token->type, dup_data);
	if (!dup_token)
		return (free(dup_data), NULL);
	return (dup_token);
}
