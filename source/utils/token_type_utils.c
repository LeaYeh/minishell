/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:33:20 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/04 23:34:04 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

bool	is_word(t_tok_typ token_type)
{
	return (token_type == T_WORD || token_type == T_ASSIGNMENT_WORD);
}

bool	is_io_red_op(t_tok_typ token_type)
{
	return (token_type == T_HERE_DOC || token_type == T_APPEND || \
		token_type == T_RED_IN || token_type == T_RED_OUT);
}

bool	is_control_op(t_tok_typ token_type)
{
	return (token_type == T_AND || token_type == T_OR || token_type == T_PIPE);
}

bool	is_subshell_symbol(t_tok_typ token_type)
{
	return (token_type == T_L_PAREN || token_type == T_R_PAREN);
}
