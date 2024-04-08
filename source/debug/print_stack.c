/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:56:05 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/08 15:39:23 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_state_stack(t_list *stack)
{
	t_list	*node;

	node = stack;
	while (node)
	{
		printf("%d <- ", get_state_from_stack(node));
		node = node->next;
	}
	printf("(NULL)\n");
}

void	print_parse_stack(t_list *node)
{
	while (node)
	{
		if (get_token_from_stack(node))
			printf("%d <- ", get_ast_from_stack(node)->element);
		node = node->next;
	}
	printf("(NULL)\n");
}
