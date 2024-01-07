/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_status_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:33:43 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/07 22:17:49 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

t_cmd_table	*get_last_simple_cmd_table(t_list_d *cmd_table_list)
{
	t_cmd_table	*last_simple_cmd_table;
	int			cur_type;

	last_simple_cmd_table = NULL;
	while (cmd_table_list && cmd_table_list->content)
	{
		cur_type = ((t_cmd_table *)cmd_table_list->content)->type;
		if (cur_type == C_PIPE || cur_type == C_AND || cur_type == C_OR)
			last_simple_cmd_table = NULL;
		else if (cur_type == C_SIMPLE_CMD || cur_type == C_NONE)
			last_simple_cmd_table = cmd_table_list->content;
		cmd_table_list = cmd_table_list->next;
	}
	return (last_simple_cmd_table);
}

int	get_cmd_table_type_from_list(t_list_d *cmd_table_list)
{
	t_cmd_table	*cmd_table;

	if (!cmd_table_list || !cmd_table_list->content)
		return (C_NONE);
	cmd_table = cmd_table_list->content;
	return (cmd_table->type);
}

// before AMD, OR and SUBSHELL_START no more simple cmd
// is_first_simple_cmd in a pipeline
bool	is_first_simple_cmd(t_list_d *cmd_table_node)
{
	int	cmd_table_type;

	if (!cmd_table_node || !cmd_table_node->content)
		return (false);
	while (cmd_table_node)
	{
		cmd_table_node = cmd_table_node->prev;
		cmd_table_type = get_cmd_table_type_from_list(cmd_table_node);
		if (cmd_table_type == C_AND || cmd_table_type == C_OR || \
			cmd_table_type == C_SUBSHELL_START)
			break ;
		if (cmd_table_type == C_SIMPLE_CMD)
			return (false);
	}
	return (true);
}
// if next node is PIPE or NULL => false, otherwise true
// because we assume that there must be control operator (include subshell) between two smiple cmd
bool	is_last_simple_cmd(t_list_d *cmd_table_node)
{
	t_list_d	*next_cmd_table_node;
	t_cmd_table	*next_cmd_table;

	next_cmd_table_node = cmd_table_node->next;
	if (!next_cmd_table_node)
		return (true);
	next_cmd_table = next_cmd_table_node->content;
	if (next_cmd_table->type != C_PIPE)
		return (true);
	return (false);
}

t_cmd_table	*get_prev_simple_cmd(t_list_d *cmd_table_node)
{
	t_cmd_table	*cmd_table;

	while (cmd_table_node)
	{
		cmd_table_node = cmd_table_node->prev;
		cmd_table = cmd_table_node->content;
		if (cmd_table->type == C_SIMPLE_CMD)
			return (cmd_table);
	}
	return (NULL);
}
