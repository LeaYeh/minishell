/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:16:41 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/04 21:16:41 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static bool	append_empty_cmd_table(t_list_d **cmd_table_list);

bool	append_cmd_table_by_scenario(
			t_tok_typ token_type, t_list_d **cmd_table_list)
{
	if (*cmd_table_list)
	{
		if (token_type == T_END)
			return (true);
		if (get_last_simple_cmd_table(*cmd_table_list) && \
			(is_io_red_op(token_type) || is_word(token_type)))
			return (true);
	}
	return (append_empty_cmd_table(cmd_table_list));
}

t_ct	*get_cmd_table_from_list(t_list_d *cmd_table_node)
{
	if (!cmd_table_node || !cmd_table_node->content)
		return (NULL);
	return (cmd_table_node->content);
}

t_ct	*get_last_simple_cmd_table(t_list_d *cmd_table_list)
{
	t_ct		*last_simple_cmd_table;
	t_ct_typ	cur_type;

	last_simple_cmd_table = NULL;
	while (cmd_table_list && cmd_table_list->content)
	{
		cur_type = get_cmd_table_type_from_list(cmd_table_list);
		if (cur_type == C_PIPE || cur_type == C_AND || cur_type == C_OR)
			last_simple_cmd_table = NULL;
		else if (cur_type == C_SIMPLE_CMD)
			last_simple_cmd_table = cmd_table_list->content;
		cmd_table_list = cmd_table_list->next;
	}
	return (last_simple_cmd_table);
}

t_ct	*get_subshell_start(t_list_d *cmd_table_node)
{
	t_ct	*cmd_table;
	int		subshell_count;

	cmd_table = NULL;
	subshell_count = 0;
	while (cmd_table_node)
	{
		cmd_table = cmd_table_node->content;
		if (cmd_table->type == C_SUBSHELL_END)
			subshell_count++;
		else if (cmd_table->type == C_SUBSHELL_START)
			subshell_count--;
		if (subshell_count <= 0)
			break ;
		cmd_table_node = cmd_table_node->prev;
	}
	return (cmd_table);
}

static bool	append_empty_cmd_table(t_list_d **cmd_table_list)
{
	t_list_d	*last_node;
	t_ct		*cmd_table;

	cmd_table = init_cmd_table();
	if (!cmd_table)
		return (false);
	last_node = ft_lstlast_d(*cmd_table_list);
	if (!last_node)
		cmd_table->id = 0;
	else
		cmd_table->id = ((t_ct *)last_node->content)->id + 1;
	if (!ft_lstnew_back_d(cmd_table_list, cmd_table))
		return (free_cmd_table(cmd_table), false);
	return (true);
}
