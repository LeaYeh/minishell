/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_post_processing.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:37:15 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/21 17:17:44 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	adjust_assignment_word_tokens(t_list *token_list);

void	finetune_token_list(t_list *token_list)
{
	if (!token_list)
		return ;
	adjust_assignment_word_tokens(token_list);
}

static void	adjust_assignment_word_tokens(t_list *token_list)
{
	t_tok_typ	prev_type;
	t_tok		*token;

	prev_type = T_NONE;
	while (token_list)
	{
		token = (t_tok *)token_list->content;
		if (token->type == T_ASSIGNMENT_WORD)
		{
			if (prev_type != T_NONE && prev_type != T_ASSIGNMENT_WORD
				&& prev_type != T_PIPE && prev_type != T_OR
				&& prev_type != T_AND && prev_type != T_L_PAREN)
			{
				token->type = T_WORD;
			}
		}
		prev_type = token->type;
		token_list = token_list->next;
	}
}
