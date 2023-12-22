/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finetune_token_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 19:37:15 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/21 19:44:04 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	finetune_token_list(t_list *token_list)
{
	if (!token_list)
		return ;
	adjust_assignment_word_tokens(token_list);
}

void	adjust_assignment_word_tokens(t_list *token_list)
{
	int		prev_type;
	t_token	*token;

	prev_type = T_UNINITIALIZED;
	while (token_list)
	{
		token = (t_token *) token_list->content;
		if (token->type == T_ASSIGNMENT_WORD)
		{
			if (prev_type != T_UNINITIALIZED && prev_type != T_ASSIGNMENT_WORD
				&& prev_type != T_PIPE && prev_type != T_OR
				&& prev_type != T_AND && prev_type != T_L_BRACKET)
			{
				token->type = T_WORD;
			}
		}
		prev_type = token->type;
		token_list = token_list->next;
	}
}
