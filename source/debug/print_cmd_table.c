/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:46:53 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/18 03:20:40 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "debug.h"

void	print_cmd_table_list(t_list_d *cmd_table_list)
{
	t_list_d	*node;
	t_ct		*cmd_table;

	ft_printf("\n\n========= cmd_table_list =========\n");
	node = cmd_table_list;
	while (node && node->content)
	{
		cmd_table = (t_ct *)node->content;
		ft_printf("========= %d =========\n", cmd_table->id);
		print_cmd_table(cmd_table);
		node = node->next;
		ft_printf("=====================\n");
	}
	ft_printf("===================================\n\n");
}

void	print_cmd_table(t_ct *cmd_table)
{
	ft_printf("type:            %d\n", cmd_table->type);
	print_simple_cmd_list(cmd_table->simple_cmd_list);
	print_assignment_list(cmd_table->assignment_list);
	print_io_red_list(cmd_table->io_red_list);
}

void	print_simple_cmd_list(t_list *simple_cmd_list)
{
	t_list	*node;

	ft_printf("simple_cmd:      ");
	node = simple_cmd_list;
	while (node && node->content)
	{
		ft_printf("%s -> ", (char *)node->content);
		node = node->next;
	}
	ft_printf("(NULL)\n");
}

void	print_assignment_list(t_list *assignment_list)
{
	t_list	*node;

	ft_printf("assignment_list: ");
	node = assignment_list;
	while (node)
	{
		ft_printf("%s -> ", (char *)node->content);
		node = node->next;
	}
	ft_printf("(NULL)\n");
}

void	print_io_red_list(t_list *io_red_list)
{
	t_list		*node;
	t_io_red	*io_red;

	ft_printf("io_red_list:\n");
	ft_printf("-----------------\n");
	node = io_red_list;
	while (node)
	{
		io_red = (t_io_red *)node->content;
		ft_printf("\ttype:    %d,\n", io_red->type);
		ft_printf("\tfilename: %s,\n", io_red->filename);
		ft_printf("\there_end: %s,\n", io_red->here_end);
		ft_printf("-----------------\n");
		node = node->next;
	}
	ft_printf("(NULL)\n");
}
