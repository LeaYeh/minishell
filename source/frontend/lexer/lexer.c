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

bool	ft_lexer(t_shell *shell)
{
	t_list	*token_data_list;

	token_data_list = NULL;
	if (!create_token_data_list(&token_data_list, shell->input_line))
	{
		ft_lstclear(&token_data_list, free);
		ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	}
	if (!token_data_list)
		return (false);
	if (!create_token_list(&shell->token_list, &token_data_list))
	{
		ft_lstclear(&token_data_list, free);
		ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	}
	set_token_type(shell->token_list);
	finetune_token_list(shell->token_list);
	if (!add_end_node(&shell->token_list))
		ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	return (true);
}
