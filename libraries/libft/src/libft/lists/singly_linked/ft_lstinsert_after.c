/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_after.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:12 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/17 18:06:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * The ft_lstinsert_after function inserts a new node or even a full linked list
 * after a given node into a singly linked list.
 *
 * @param lst   A double pointer to the node after which the new list should be
 *              inserted.
 *              If *lst is NULL, the new node is set as the first node.
 * @param new   The new node or list to be inserted into the list.
 */

#include "libft.h"

void	ft_lstinsert_after(t_list **lst, t_list *new)
{
	t_list	*last_new;
	t_list	*old;

	if (lst != NULL && new != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			old = (*lst)->next;
			(*lst)->next = new;
			last_new = new;
			while (last_new->next != NULL)
				last_new = last_new->next;
			last_new->next = old;
		}
	}
	return ;
}
