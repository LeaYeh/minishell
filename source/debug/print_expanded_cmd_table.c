/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expanded_cmd_table.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:40:56 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/03 16:17:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "expander.h"

static bool	expand_cmd_name(t_cmd_table *cmd_table, t_shell *shell)
{
	if (!ft_expander(&cmd_table->cmd_name, shell))
		return (false);
	return (true);
}

static bool	expand_cmd_args(t_cmd_table *cmd_table, t_shell *shell)
{
	t_list	*node;

	node = cmd_table->cmd_args;
	while (node)
	{
		if (!ft_expander((char **)&node->content, shell))
			return (false);
		node = node->next;
	}
	return (true);
}

static bool	expand_assignment_list(t_cmd_table *cmd_table, t_shell *shell)
{
	t_list	*node;

	node = cmd_table->assignment_list;
	while (node)
	{
		if (!ft_expander((char **)&node->content, shell))
			return (false);
		node = node->next;
	}
	return (true);
}

static bool	expand_io_red_list(t_cmd_table *cmd_table, t_shell *shell)
{
	t_list	*node;

	node = cmd_table->io_red_list;
	while (node)
	{
		if (!ft_expander(&((t_io_red *)node->content)->in_file, shell))
			return (false);
		if (!ft_expander(&((t_io_red *)node->content)->out_file, shell))
			return (false);
		if (!ft_expander(&((t_io_red *)node->content)->here_end, shell))
			return (false);
		node = node->next;
	}
	return (true);
}

static bool	expand_cmd_table(t_cmd_table *cmd_table, t_shell *shell)
{
	if (!expand_cmd_name(cmd_table, shell))
		return (false);
	if (!expand_cmd_args(cmd_table, shell))
		return (false);
	if (!expand_assignment_list(cmd_table, shell))
		return (false);
	if (!expand_io_red_list(cmd_table, shell))
		return (false);
	return (true);
}

bool	print_expanded_cmd_table_list(t_shell *shell)
{
	t_list_d	*node;
	t_cmd_table	*cmd_table;

	printf("\033[1;34m\n\n===== EXPANDED cmd_table_list =====\n\033[0m");
	node = shell->cmd_table_list;
	while (node)
	{
		cmd_table = (t_cmd_table *)node->content;
		// if (cmd_table->type == C_SIMPLE_CMD)
		// {
			printf("\033[1;31mBEFORE EXPANSION:\n\033[0m");
			printf("\033[0;31m========= %d =========\n\033[0m", cmd_table->id);
			print_cmd_table(cmd_table);
			printf("\033[0;31m=====================\n\033[0m");
			if (!expand_cmd_table(cmd_table, shell))
				return (false);
			printf("\033[1;32mAFTER EXPANSION:\n\033[0m");
			printf("\033[0;32m========= %d =========\n\033[0m", cmd_table->id);
			print_cmd_table(cmd_table);
			printf("\033[0;32m=====================\n\033[0m");
		// }
		node = node->next;
	}
	printf("\033[1;34m====================================\n\n\033[0m");
	return (true);
}
