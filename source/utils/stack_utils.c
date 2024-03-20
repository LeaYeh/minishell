/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:55:34 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/23 18:41:05 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

bool	drop_num_stack(t_list **stack, int num, void (*del)(void *))
{
	int		i;
	t_list	*node;

	i = 0;
	while (i < num)
	{
		node = ft_lstpop_front(stack);
		if (!node)
			return (false);
		ft_lstdelone(node, del);
		i++;
	}
	return (true);
}

t_list	*pop_num_stack(t_list **stack, int num)
{
	t_list	*head;
	t_list	*node;
	int		i;

	head = NULL;
	i = 0;
	while (i < num)
	{
		node = ft_lstpop_front(stack);
		if (!node)
			return (NULL);
		ft_lstadd_front(&head, node);
		i++;
	}
	return (head);
}

int	get_state_from_stack(t_list *node)
{
	if (!node || !node->content)
		return (UNDEFINED_STATE);
	return (*((int *)node->content));
}

t_token	*get_token_from_stack(t_list *node)
{
	if (!node)
		return (NULL);
	return ((t_token *)node->content);
}
