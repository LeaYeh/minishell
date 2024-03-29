/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expanded_cmd_table.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:40:56 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/26 22:46:29 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_unexpanded_cmd_table(t_cmd_table *cmd_table)
{
	printf(STY_BLD STY_RED "BEFORE EXPANSION:\n" STY_RES);
	printf(STY_RED "========= %d =========\n" STY_RES, cmd_table->id);
	print_cmd_table(cmd_table);
	printf(STY_RED "=====================\n" STY_RES);
}

bool	print_expanded_cmd_table(t_cmd_table *cmd_table, t_shell *shell)
{
	printf(STY_BLD STY_GRN "AFTER EXPANSION:\n" STY_RES);
	printf(STY_GRN "========= %d =========\n" STY_RES, cmd_table->id);
	printf("type:            %d\n", cmd_table->type);
	if (!print_expanded_simple_cmd_list(cmd_table, shell))
		return (false);
	if (!print_expanded_assignment_list(cmd_table, shell))
		return (false);
	if (!print_expanded_io_red_list(cmd_table, shell))
		return (false);
	printf(STY_GRN "=====================\n" STY_RES);
	return (true);
}

void	print_operator_cmd_table(t_cmd_table *cmd_table)
{
	printf(STY_BLD STY_MAG "OPERATOR NODE:\n" STY_RES);
	printf(STY_MAG "========= %d =========\n" STY_RES, cmd_table->id);
	print_cmd_table(cmd_table);
	printf(STY_MAG "=====================\n" STY_RES);
}

bool	print_expanded_cmd_table_list(t_shell *shell)
{
	t_list_d	*node;
	t_cmd_table	*cmd_table;

	printf(STY_BLD STY_BLU "\n\n===== EXPANDED cmd_table_list =====\n" STY_RES);
	node = shell->cmd_table_list;
	while (node)
	{
		cmd_table = (t_cmd_table *)node->content;
		if (cmd_table->type == C_SIMPLE_CMD)
		{
			print_unexpanded_cmd_table(cmd_table);
			if (!print_expanded_cmd_table(cmd_table, shell))
				return (false);
		}
		else
			print_operator_cmd_table(cmd_table);
		node = node->next;
	}
	printf(STY_BLD STY_BLU "====================================" STY_RES "\n");
	return (true);
}
