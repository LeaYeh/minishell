/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_symbol_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:56:47 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 18:11:52 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static bool	fill_red_node(t_io_red *io_red, t_tok_typ type, char *data);
static bool	fill_redirect(t_list **token_list, t_ct *cmd_table);

bool	fill_redirect_by_scenario(
			t_list **token_list, t_list_d **cmd_table_list)
{
	t_ct		*cmd_table;
	t_list_d	*cmd_table_node;

	cmd_table_node = ft_lstlast_d(*cmd_table_list);
	cmd_table = cmd_table_node->content;
	if (cmd_table->type == C_SIMPLE_CMD)
	{
		if (!fill_redirect(token_list, cmd_table))
			return (false);
	}
	else
	{
		cmd_table = get_subshell_start(cmd_table_node);
		if (!fill_redirect(token_list, cmd_table))
			return (false);
	}
	*token_list = (*token_list)->next;
	return (true);
}

void	fill_control_op(t_list **token_list, t_list_d **cmd_table_list)
{
	t_tok	*token;
	t_ct	*cmd_table;

	token = get_token_from_list(*token_list);
	cmd_table = ft_lstlast_d(*cmd_table_list)->content;
	if (token->type == T_AND)
		cmd_table->type = C_AND;
	else if (token->type == T_OR)
		cmd_table->type = C_OR;
	else if (token->type == T_PIPE)
		cmd_table->type = C_PIPE;
}

void	fill_parenthesis(t_list **token_list, t_list_d **cmd_table_list)
{
	t_tok	*token;
	t_ct	*cmd_table;

	token = get_token_from_list(*token_list);
	cmd_table = ft_lstlast_d(*cmd_table_list)->content;
	if (token->type == T_L_PAREN)
		cmd_table->type = C_SUBSHELL_START;
	else if (token->type == T_R_PAREN)
		cmd_table->type = C_SUBSHELL_END;
}

static bool	fill_redirect(t_list **token_list, t_ct *cmd_table)
{
	t_tok		*red_op;
	t_tok		*filename;
	t_io_red	*io_red;

	red_op = get_token_from_list(*token_list);
	filename = get_token_from_list((*token_list)->next);
	io_red = init_io_red();
	if (!io_red)
		return (false);
	if (!fill_red_node(io_red, red_op->type, filename->data))
		return (free_io_red(io_red), false);
	if (!ft_lstnew_back(&cmd_table->io_red_list, io_red))
		return (free_io_red(io_red), false);
	return (true);
}

static bool	fill_red_node(t_io_red *io_red, t_tok_typ type, char *data)
{
	char	*dup_data;

	dup_data = ft_strdup(data);
	if (!dup_data)
		return (false);
	io_red->type = type;
	if (type == T_HERE_DOC)
		io_red->here_end = dup_data;
	else
		io_red->filename = dup_data;
	return (true);
}
