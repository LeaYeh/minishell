/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:31:35 by codespace         #+#    #+#             */
/*   Updated: 2023/12/21 19:46:04 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "utils.h"

/*
NOTES:
- END token at the end
- echo>out should be split into 3 tokens
- Assignment word!
	[x] =abc -> WORD
	[x] abc=abc -> ASSIGNMENT_WORD
	[x] a"b"c=456 -> WORD (unspecified)
	[x] export >a=def -> a=def will be a WORD?

	parser branch has useful token functions in utils - USE THEM! (after parser-branch merged)
*/

/* < > << >> | || && ( ) */

bool	ft_lexer(t_shell *shell)
{
	t_list	*token_data_list;

	if (!shell || !shell->input_line)
		return (NULL);
	token_data_list = get_token_data_list(shell->input_line);
	if (!token_data_list)
		return (false);
	if (!create_token_list(&shell->token_list, &token_data_list))
		return (false);
	set_token_type(shell->token_list);
	finetune_token_list(shell->token_list);
	if (!add_end_node(&shell->token_list))
		return (false);
	return (true);
}
