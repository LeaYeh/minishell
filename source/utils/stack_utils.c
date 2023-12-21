/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:55:34 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/18 21:46:44 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

bool	drop_num_stack(t_stack **stack, int num, void (*del)(void *))
{
	int		i;
	t_stack	*node;

	i = 0;
	while (i < num)
	{
		node = ft_stkpop(stack);
		if (!node)
			return (false);
		ft_stkdelone(node, del);
		i++;
	}
	return (true);
}

int	get_state_from_stack(t_stack *node)
{
	return (*((int *)node->content));
}

t_token	*get_token_from_stack(t_stack *node)
{
	return ((t_token *)node->content);
}

void	print_state_stack(t_stack *stack)
{
	t_stack	*node;

	node = stack;
	while (node)
	{
		printf("%d <- ", get_state_from_stack(node));
		node = node->next;
	}
	printf("(NULL)\n");
}

void	print_parse_stack(t_stack *node)
{
	while (node)
	{
		if (get_token_from_stack(node))
			printf("%d <- ", get_token_from_stack(node)->type);
		node = node->next;
	}
	printf("(NULL)\n");
}
