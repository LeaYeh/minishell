/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:46:53 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/30 18:14:41 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

void	print_io_red_list(t_list *io_red_list)
{
	t_list		*node;
	t_io_red	*io_red;

	printf("io_red_list:\n");
	printf("-----------------\n");
	node = io_red_list;
	while (node)
	{
		io_red = (t_io_red *)node->content;
		printf("\tin_file: %s,\n", io_red->in_file);
		printf("\tout_file: %s,\n", io_red->out_file);
		printf("\there_end: %s,\n", io_red->here_end);
		printf("\tred_in: %d,\n", io_red->red_in);
		printf("\tred_out: %d,\n", io_red->red_out);
		printf("-----------------\n");
		node = node->next;
	}
	printf("(NULL)\n");
}

void	print_cmd_args_list(t_list *cmd_args)
{
	t_list	*node;

	printf("cmd_args:        ");
	node = cmd_args;
	while (node && node->content)
	{
		printf("%s -> ", (char *)node->content);
		node = node->next;
	}
	printf("(NULL)\n");
}

void	print_assignment_list(t_list *assignment_list)
{
	t_list	*node;

	printf("assignment_list: ");
	node = assignment_list;
	while (node)
	{
		printf("%s -> ", (char *)node->content);
		node = node->next;
	}
	printf("(NULL)\n");
}

void	print_cmd_table(t_cmd_table *cmd_table)
{
	printf("type:            %d\n", cmd_table->type);
	printf("cmd_name:        %s\n", cmd_table->cmd_name);
	print_cmd_args_list(cmd_table->cmd_args);
	print_assignment_list(cmd_table->assignment_list);
	print_io_red_list(cmd_table->io_red_list);
}

void	print_cmd_table_list(t_list_d *cmd_table_list)
{
	t_list_d	*node;
	t_cmd_table	*cmd_table;

	printf("\n\n========= cmd_table_list =========\n");
	node = cmd_table_list;
	while (node && node->content)
	{
		cmd_table = (t_cmd_table *)node->content;
		printf("========= %d =========\n", cmd_table->id);
		print_cmd_table(cmd_table);
		node = node->next;
		printf("=====================\n");
	}
	printf("===================================\n\n");
}
