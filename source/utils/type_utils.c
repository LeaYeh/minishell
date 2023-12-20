/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:33:20 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/20 18:21:01 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

char	*ft_get_token_type_str(int type)
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
