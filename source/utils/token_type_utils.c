/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:33:20 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 17:53:13 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

bool	is_control_op(int token_type)
{
	return (token_type == T_AND || token_type == T_OR || token_type == T_PIPE);
}

bool	is_word(int token_type)
{
	return (token_type == T_WORD || token_type == T_ASSIGNMENT_WORD);
}

bool	is_io_red_op(int token_type)
{
	return (token_type == T_HERE_DOC || token_type == T_APPEND || \
		token_type == T_RED_IN || token_type == T_RED_OUT);
}

bool	is_subshell_symbol(int token_type)
{
	return (token_type == T_L_BRACKET || token_type == T_R_BRACKET);
}
