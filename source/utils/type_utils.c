/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:33:20 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/29 17:11:37 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

char	*ft_get_token_type_str(t_token_type type)
{
	if (type == T_WORD)
		return ("WORD");
	else if (type == T_ASSIGNMENT_WORD)
		return ("ASSIGNMENT_WORD");
	else if (type == T_RED_IN)
		return ("RED_IN");
	else if (type == T_RED_OUT)
		return ("RED_OUT");
	else if (type == T_HERE_DOC)
		return ("HEREDOC");
	else if (type == T_APPEND)
		return ("APPEND");
	else if (type == T_PIPE)
		return ("PIPE");
	else if (type == T_OR)
		return ("OR");
	else if (type == T_AND)
		return ("AND");
	else if (type == T_L_BRACKET)
		return ("L_BRACKET");
	else if (type == T_R_BRACKET)
		return ("R_BRACKET");
	else if (type == T_END)
		return ("END");
	return (NULL);
}

bool	is_control_op(t_token_type token_type)
{
	return (token_type == T_AND || token_type == T_OR || token_type == T_PIPE);
}

// bool	is_identifier(t_token_type token_type)
// {
// 	return (token_type < 100 && token_type >= 0);
// }


// bool	is_rule(t_token_type token_type)
// {
// 	return (token_type >= 100);
// }

bool	is_word(t_token_type token_type)
{
	return (token_type == T_WORD || token_type == T_ASSIGNMENT_WORD);
}

bool	is_io_red_op(t_token_type token_type)
{
	return (token_type == T_HERE_DOC || token_type == T_APPEND || \
		token_type == T_RED_IN || token_type == T_RED_OUT);
}

bool	is_subshell_symbol(t_token_type token_type)
{
	return (token_type == T_L_BRACKET || token_type == T_R_BRACKET);
}
