/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_symbol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:07:59 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/30 20:03:25 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	fill_bracket(t_list **token_list, t_list_d **cmd_table_list)
{
	t_token		*token;
	t_cmd_table	*cmd_table;

	token = get_token_from_list(*token_list);
	cmd_table = ft_lstlast_d(*cmd_table_list)->content;
	if (token->type == T_L_BRACKET)
		cmd_table->type = C_SUBSHELL_START;
	else if (token->type == T_R_BRACKET)
		cmd_table->type = C_SUBSHELL_END;
}

bool	fill_red_node(t_io_red *io_red, int type, char *data)
{
	char	*dup_data;

	dup_data = ft_strdup(data);
	if (!dup_data)
		return (false);
	io_red->type = type;
	if (type == T_RED_IN)
		io_red->in_file = dup_data;
	else if (type == T_HERE_DOC)
		io_red->here_end = dup_data;
	else if (type == T_RED_OUT || type == T_APPEND)
		io_red->out_file = dup_data;
	return (true);
}

bool	fill_redirect(t_list **token_list, t_cmd_table *cmd_table)
{
	t_token		*red_op;
	t_token		*filename;
	t_io_red	*io_red;
	t_list		*node;

	red_op = get_token_from_list(*token_list);
	filename = get_token_from_list((*token_list)->next);
	io_red = init_io_red();
	if (!io_red)
		return (false);
	if (!fill_red_node(io_red, red_op->type, filename->data))
		return (free_io_red(io_red), false);
	node = ft_lstnew(io_red);
	if (!node)
		return (free_io_red(io_red), false);
	ft_lstadd_back(&cmd_table->io_red_list, node);
	return (true);
}

bool	handle_redirect(t_list **token_list, t_list_d **cmd_table_list)
{
	t_cmd_table	*cmd_table;
	t_list_d	*cmd_table_node;

	cmd_table_node = ft_lstlast_d(*cmd_table_list);
	cmd_table = cmd_table_node->content;
	if (cmd_table->type == C_NONE)
		cmd_table->type = C_SIMPLE_CMD;
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
	t_token		*token;
	t_cmd_table	*cmd_table;

	token = get_token_from_list(*token_list);
	cmd_table = ft_lstlast_d(*cmd_table_list)->content;
	if (token->type == T_AND)
		cmd_table->type = C_AND;
	else if (token->type == T_OR)
		cmd_table->type = C_OR;
	else if (token->type == T_PIPE)
		cmd_table->type = C_PIPE;
}

bool	handle_symbol_token(t_list **token_list, t_list_d **cmd_table_list)
{
	int	token_type;

	token_type = get_token_type_from_list(*token_list);
	if (is_io_red_op(token_type))
	{
		if (handle_redirect(token_list, cmd_table_list))
			return (true);
	}
	else if (is_control_op(token_type))
	{
		fill_control_op(token_list, cmd_table_list);
		return (true);
	}
	else if (is_subshell_symbol(token_type))
	{
		fill_bracket(token_list, cmd_table_list);
		return (true);
	}
	return (false);
}
