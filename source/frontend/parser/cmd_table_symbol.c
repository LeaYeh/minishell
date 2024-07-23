/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_symbol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:07:59 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 18:13:36 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

bool	handle_symbol_token(t_list **token_list, t_list_d **cmd_table_list)
{
	t_tok_typ	token_type;

	token_type = get_token_type_from_list(*token_list);
	if (is_io_red_op(token_type))
	{
		if (fill_redirect_by_scenario(token_list, cmd_table_list))
			return (true);
	}
	else if (is_control_op(token_type))
	{
		fill_control_op(token_list, cmd_table_list);
		return (true);
	}
	else if (is_subshell_symbol(token_type))
	{
		fill_parenthesis(token_list, cmd_table_list);
		return (true);
	}
	return (false);
}
