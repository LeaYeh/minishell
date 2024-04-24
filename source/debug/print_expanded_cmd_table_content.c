/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expanded_cmd_table_content.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:45:55 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/26 22:46:03 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "expander.h"

bool	print_expanded_simple_cmd_list(t_ct *cmd_table, t_sh *shell)
{
	t_list	*node;

	ft_dprintf(STDERR_FILENO, "simple_cmd:      ");
	node = cmd_table->simple_cmd_list;
	while (node)
	{
		if (!print_expanded_str(node->content,
				shell, E_PARAM | E_SPLIT_WORDS | E_WILDCARD | E_RM_QUOTES))
			return (false);
		ft_dprintf(STDERR_FILENO, " -> ");
		node = node->next;
	}
	ft_dprintf(STDERR_FILENO, "(NULL)\n");
	return (true);
}

bool	print_expanded_assignment_list(t_ct *cmd_table, t_sh *shell)
{
	t_list	*node;

	ft_dprintf(STDERR_FILENO, "assignment_list: ");
	node = cmd_table->assignment_list;
	while (node)
	{
		if (!print_expanded_str(node->content,
				shell, E_PARAM | E_SPLIT_WORDS | E_WILDCARD | E_RM_QUOTES))
			return (false);
		ft_dprintf(STDERR_FILENO, " -> ");
		node = node->next;
	}
	ft_dprintf(STDERR_FILENO, "(NULL)\n");
	return (true);
}

bool	print_expanded_io_red_list(t_ct *cmd_table, t_sh *shell)
{
	t_list		*node;
	t_io_red	*io_red;

	ft_dprintf(STDERR_FILENO, "io_red_list:\n");
	ft_dprintf(STDERR_FILENO, "-----------------\n");
	node = cmd_table->io_red_list;
	while (node)
	{
		io_red = (t_io_red *)node->content;
		ft_dprintf(STDERR_FILENO, "\ttype:     %d", io_red->type);
		ft_dprintf(STDERR_FILENO, "\n\filename:  ");
		if (!print_expanded_str(
				io_red->filename, shell, E_PARAM | E_WILDCARD | E_RM_QUOTES))
			return (false);
		ft_dprintf(STDERR_FILENO, "\n\there_end: ");
		if (!print_expanded_str(io_red->here_end, shell, E_RM_QUOTES))
			return (false);
		ft_dprintf(STDERR_FILENO, "\n-----------------\n");
		node = node->next;
	}
	return (true);
}

bool	print_expanded_str(char *str, t_sh *shell, t_expd_op op_mask)
{
	t_list	*expanded_list;
	t_list	*cur;
	int		ret;

	expanded_list = NULL;
	ret = expander(str, &expanded_list, shell, op_mask);
	if (ret == MALLOC_ERROR)
		return (ft_dprintf(STDERR_FILENO, "malloc failed in expander"), false);
	if (ret == BAD_SUBSTITUTION)
		ft_dprintf(STDERR_FILENO, STY_RED "Bad substitution." STY_RES);
	else if (!expanded_list)
		return (ft_dprintf(STDERR_FILENO, "(NULL)"), true);
	cur = expanded_list;
	while (cur)
	{
		ft_dprintf(STDERR_FILENO, STY_BLU "|" STY_RES "%s" STY_BLU "|" STY_RES,
			(char *)expanded_list->content);
		cur = cur->next;
	}
	ft_lstclear(&expanded_list, free);
	return (true);
}
