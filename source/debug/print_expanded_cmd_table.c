/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expanded_cmd_table.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:40:56 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/18 15:41:46 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "expander.h"

bool	expand_and_print(char *str, t_shell *shell)
{
	t_list	*expanded_list;
	t_list	*cur;
	int		ret;

	expanded_list = NULL;
	ret = expander(str, &expanded_list, shell,
			E_EXPAND | E_SPLIT_WORDS | E_RM_QUOTES);
	if (ret == MALLOC_ERROR)
		return (printf("malloc failed in expander"), false);
	if (ret == BAD_SUBSTITUTION)
		printf(STY_RED "Bad substitution." STY_RES);
	else if (!expanded_list)
		return (printf("(NULL)"), true);
	cur = expanded_list;
	while (cur)
	{
		printf(STY_BLU "|" STY_RES "%s" STY_BLU "|" STY_RES,
			(char *)expanded_list->content);
		cur = cur->next;
	}
	ft_lstclear(&expanded_list, free);
	return (true);
}

bool	print_expanded_simple_cmd_list(t_cmd_table *cmd_table, t_shell *shell)
{
	t_list	*node;

	printf("simple_cmd:      ");
	node = cmd_table->simple_cmd_list;
	while (node)
	{
		if (!expand_and_print(node->content, shell))
			return (false);
		printf(" -> ");
		node = node->next;
	}
	printf("(NULL)\n");
	return (true);
}

bool	print_expanded_assignment_list(t_cmd_table *cmd_table, t_shell *shell)
{
	t_list	*node;

	printf("assignment_list: ");
	node = cmd_table->assignment_list;
	while (node)
	{
		if (!expand_and_print(node->content, shell))
			return (false);
		printf(" -> ");
		node = node->next;
	}
	printf("(NULL)\n");
	return (true);
}

bool	print_expanded_io_red_list(t_cmd_table *cmd_table, t_shell *shell)
{
	t_list		*node;
	t_io_red	*io_red;

	printf("io_red_list:\n");
	printf("-----------------\n");
	node = cmd_table->io_red_list;
	while (node)
	{
		io_red = (t_io_red *)node->content;
		printf("\ttype:     %d", io_red->type);
		printf("\n\filename:  ");
		if (!expand_and_print(io_red->filename, shell))
			return (false);
		printf("\n\there_end: ");
		if (!expand_and_print(io_red->here_end, shell))
			return (false);
		printf("\n-----------------\n");
		node = node->next;
	}
	return (true);
}

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
