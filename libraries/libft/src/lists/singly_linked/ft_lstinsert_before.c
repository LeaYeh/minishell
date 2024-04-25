/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_before.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:15:15 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/27 14:01:12 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_lstinsert_before function inserts a new node or even a full linked
 * list before a given node into a singly linked list.
 *
 * @param lst    The address of the pointer to the list in which the new node or
 *               list should be inserted.
 *               If *lst is NULL, the new node is set as the first node.
 * @param cur    The node before which the new node or list should be inserted.
 *               If cur cannot be found in lst, the function does nothing.
 * @param new    The new node or list to be inserted into the list.
 *
 * @return       No return value.
 *
 */
void	ft_lstinsert_before(t_list **lst, t_list *cur, t_list *new)
{
	t_list	*next;
	t_list	*prev;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == cur || *lst == NULL)
	{
		ft_lstlast(new)->next = *lst;
		*lst = new;
		return ;
	}
	prev = *lst;
	while (prev != NULL && prev->next != cur)
		prev = prev->next;
	if (prev == NULL)
		return ;
	next = prev->next;
	prev->next = new;
	ft_lstlast(new)->next = next;
	return ;
}
