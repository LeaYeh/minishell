/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:31:35 by codespace         #+#    #+#             */
/*   Updated: 2024/01/07 14:09:24 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "clean.h"

bool	lexer(t_sh *shell)
{
	t_list	*token_data_list;

	token_data_list = NULL;
	if (!create_token_data_list(&token_data_list, shell->input_line))
	{
		ft_lstclear(&token_data_list, free);
		clean_and_exit_shell(shell, PREPROCESS_ERROR, "lexer malloc failed");
	}
	if (!token_data_list)
		return (false);
	if (!create_token_list(&shell->token_list, &token_data_list))
	{
		ft_lstclear(&token_data_list, free);
		clean_and_exit_shell(shell, PREPROCESS_ERROR, "lexer malloc failed");
	}
	set_token_type(shell->token_list);
	finetune_token_list(shell->token_list);
	if (!append_end_node(&shell->token_list))
		clean_and_exit_shell(shell, PREPROCESS_ERROR, "lexer malloc failed");
	return (true);
}
