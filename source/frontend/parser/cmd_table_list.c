/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:25:20 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/06 19:47:28 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static bool	handle_current_token(
				t_list **token_list, t_list_d **cmd_table_list);
static void	fill_subshell_level(t_list_d *cmd_table_list);

t_list_d	*build_cmd_table_list(t_list *token_list)
{
	t_list_d	*cmd_table_list;

	cmd_table_list = NULL;
	while (token_list)
	{
		if (!handle_current_token(&token_list, &cmd_table_list))
			return (
				ft_lstclear_d(&cmd_table_list, (void *)free_cmd_table), NULL);
		token_list = token_list->next;
	}
	fill_subshell_level(cmd_table_list);
	return (cmd_table_list);
}

static bool	handle_current_token(
				t_list **token_list, t_list_d **cmd_table_list)
{
	t_tok_typ	token_type;

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

static void	fill_subshell_level(t_list_d *cmd_table_list)
{
	t_ct	*cmd_table;
	int		level;

	level = 0;
	while (cmd_table_list)
	{
		cmd_table = cmd_table_list->content;
		if (cmd_table->type == C_SUBSHELL_START)
			cmd_table->subshell_level = level++;
		else if (cmd_table->type == C_SUBSHELL_END)
			cmd_table->subshell_level = --level;
		cmd_table_list = cmd_table_list->next;
	}
}
