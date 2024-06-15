/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_traversal_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:12:24 by codespace         #+#    #+#             */
/*   Updated: 2024/01/14 17:22:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	move_past_pipeline(t_list_d **cmd_table_node)
{
	t_ct	*cmd_table;

	cmd_table = (*cmd_table_node)->content;
	while (cmd_table->type != C_SUBSHELL_END && \
		cmd_table->type != C_AND && cmd_table->type != C_OR)
	{
		if (cmd_table->type == C_SUBSHELL_START)
			move_past_subshell(cmd_table_node);
		else
			*cmd_table_node = (*cmd_table_node)->next;
		if (*cmd_table_node == NULL)
			return ;
		cmd_table = (*cmd_table_node)->content;
	}
}

void	move_past_subshell(t_list_d **cmd_table_node)
{
	t_ct_typ	cmd_table_type;
	int			subshell_count;

	subshell_count = 1;
	while (subshell_count > 0)
	{
		*cmd_table_node = (*cmd_table_node)->next;
		cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
		if (cmd_table_type == C_SUBSHELL_START)
			subshell_count++;
		else if (cmd_table_type == C_SUBSHELL_END)
			subshell_count--;
	}
	*cmd_table_node = (*cmd_table_node)->next;
}
