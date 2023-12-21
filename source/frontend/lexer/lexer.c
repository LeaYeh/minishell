/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:31:35 by codespace         #+#    #+#             */
/*   Updated: 2023/12/21 20:09:35 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
