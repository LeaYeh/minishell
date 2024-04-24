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

	ft_dprintf(STDERR_FILENO, "\n\n========= cmd_table_list =========\n");
	node = cmd_table_list;
	while (node && node->content)
	{
		cmd_table = (t_ct *)node->content;
		ft_dprintf(STDERR_FILENO, "========= %d =========\n", cmd_table->id);
		print_cmd_table(cmd_table);
		node = node->next;
		ft_dprintf(STDERR_FILENO, "=====================\n");
	}
	ft_dprintf(STDERR_FILENO, "===================================\n\n");
}

void	print_cmd_table(t_ct *cmd_table)
{
	ft_dprintf(STDERR_FILENO, "type:            %d\n", cmd_table->type);
	print_simple_cmd_list(cmd_table->simple_cmd_list);
	print_assignment_list(cmd_table->assignment_list);
	print_io_red_list(cmd_table->io_red_list);
}

void	print_simple_cmd_list(t_list *simple_cmd_list)
{
	t_list	*node;

	ft_dprintf(STDERR_FILENO, "simple_cmd:      ");
	node = simple_cmd_list;
	while (node && node->content)
	{
		ft_dprintf(STDERR_FILENO, "%s -> ", (char *)node->content);
		node = node->next;
	}
	ft_dprintf(STDERR_FILENO, "(NULL)\n");
}

void	print_assignment_list(t_list *assignment_list)
{
	t_list	*node;

	ft_dprintf(STDERR_FILENO, "assignment_list: ");
	node = assignment_list;
	while (node)
	{
		ft_dprintf(STDERR_FILENO, "%s -> ", (char *)node->content);
		node = node->next;
	}
	ft_dprintf(STDERR_FILENO, "(NULL)\n");
}

void	print_io_red_list(t_list *io_red_list)
{
	t_list		*node;
	t_io_red	*io_red;

	ft_dprintf(STDERR_FILENO, "io_red_list:\n");
	ft_dprintf(STDERR_FILENO, "-----------------\n");
	node = io_red_list;
	while (node)
	{
		io_red = (t_io_red *)node->content;
		ft_dprintf(STDERR_FILENO, "\ttype:    %d,\n", io_red->type);
		ft_dprintf(STDERR_FILENO, "\tfilename: %s,\n", io_red->filename);
		ft_dprintf(STDERR_FILENO, "\there_end: %s,\n", io_red->here_end);
		ft_dprintf(STDERR_FILENO, "-----------------\n");
		node = node->next;
	}
	ft_dprintf(STDERR_FILENO, "(NULL)\n");
}
