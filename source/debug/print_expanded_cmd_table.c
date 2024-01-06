/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expanded_cmd_table.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:40:56 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/06 13:16:28 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "expander.h"

bool	expand_and_print(char **str, t_shell *shell)
{
	t_list	*expanded_list;
	t_list	*cur;

	expanded_list = NULL;
	if (!ft_expander(str, &expanded_list, shell))
	{
		if (!*str)
		{
			printf("%s", *str);
			return (false);
		}
		printf(STY_RED "Expander error." STY_RES);
	}
	if (!expanded_list)
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

bool	print_expanded_cmd_name(t_cmd_table *cmd_table, t_shell *shell)
{
	printf("cmd_name:        ");
	if (!expand_and_print(&cmd_table->cmd_name, shell))
		return (false);
	printf("\n");
	return (true);
}

bool	print_expanded_cmd_args(t_cmd_table *cmd_table, t_shell *shell)
{
	t_list	*node;

	printf("cmd_args:        ");
	node = cmd_table->cmd_args;
	while (node)
	{
		if (!expand_and_print((char **)&node->content, shell))
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
		if (!expand_and_print((char **)&node->content, shell))
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
		printf("\n\tin_file:  ");
		if (!expand_and_print(&io_red->in_file, shell))
			return (false);
		printf("\n\tout_file: ");
		if (!expand_and_print(&io_red->out_file, shell))
			return (false);
		printf("\n\there_end: ");
		if (!expand_and_print(&io_red->here_end, shell))
			return (false);
		printf("\n\tred_in:  %d", io_red->red_in);
		printf("\n\tred_out: %d", io_red->red_out);
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
	if (!print_expanded_cmd_name(cmd_table, shell))
		return (false);
	if (!print_expanded_cmd_args(cmd_table, shell))
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
	printf(STY_BLD STY_BLU "====================================\n\n" STY_RES);
	return (true);
}
