/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdrop_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:58:36 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/17 11:44:38 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_lstdrop_node function removes a node from a singly linked list.
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
void	ft_lstdrop_node(t_list **lst, t_list **node, void (*del)(void *))
{
	t_list	*prev;
	t_list	*next;

	if (lst == NULL || *lst == NULL || node == NULL || *node == NULL)
		return ;
	if (*lst == *node)
	{
		*lst = (*lst)->next;
		ft_lstdelone(*node, del);
		*node = *lst;
		return ;
	}
	prev = *lst;
	while (prev != NULL && prev->next != *node)
		prev = prev->next;
	if (prev == NULL)
		return ;
	next = prev->next->next;
	ft_lstdelone(*node, del);
	prev->next = next;
	*node = next;
	return ;
}
