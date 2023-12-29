/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:25:20 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/29 20:20:34 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

bool	handle_current_token(t_list **token_list, t_list_d **cmd_table_list)
{
	int	token_type;

	token_type = get_token_type_from_list(*token_list);
	if (!append_cmd_table_by_scenario(token_type, cmd_table_list))
		return (false);
	if (is_word(token_type))
	{
		if (handle_word_token(token_list, cmd_table_list))
			return (true);
	}
	else if (is_control_op(token_type) || is_io_red_op(token_type) || \
			is_subshell_symbol(token_type))
	{
		if (handle_symbol_token(token_list, cmd_table_list))
			return (true);
	}
	else if (token_type == T_END)
		return (true);
	return (false);
}

t_list_d	*build_cmd_table_list(t_list *token_list)
{
	t_list_d	*cmd_table_list;

	cmd_table_list = NULL;
	print_token_list(token_list);
	while (token_list)
	{
		if (!handle_current_token(&token_list, &cmd_table_list))
			return (
				ft_lstclear_d(&cmd_table_list, (void *)free_cmd_table), NULL);
		token_list = token_list->next;
	}
	return (cmd_table_list);
}
