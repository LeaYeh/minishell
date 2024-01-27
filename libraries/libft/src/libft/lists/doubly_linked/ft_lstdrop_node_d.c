/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdrop_node_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:03:55 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/17 11:54:23 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_lstdrop_node_d function removes a node from a doubly linked list.
 * The pointer of the node to be removed will be moved forward to the node
 * coming after the deleted node.
 * If the node to be deleted cannot be found in the list, the function does
 * nothing.
 *
 * @param lst     The address of the pointer to the list to remove a node from.
 * @param node    The address of the node to be removed.
 * @param del     The function to free the content of the node with.
 *
 * @return        No return value.
 *
 */
void	ft_lstdrop_node_d(t_list_d **lst, t_list_d **node, void (*del)(void *))
{
	t_list_d	*cur;
	t_list_d	*prev;
	t_list_d	*next;

	if (lst == NULL || *lst == NULL || node == NULL || *node == NULL)
		return ;
	if (*lst == *node)
		*lst = (*lst)->next;
	else
	{
		cur = *lst;
		while (cur != NULL && cur != *node)
			cur = cur->next;
		if (cur == NULL)
			return ;
	}
	prev = (*node)->prev;
	next = (*node)->next;
	ft_lstdelone_d(*node, del);
	*node = next;
	if (prev != NULL)
		prev->next = next;
	if (next != NULL)
		next->prev = prev;
	return ;
}
