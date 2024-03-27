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
