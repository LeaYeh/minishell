/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_tail.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:35:15 by ldulling          #+#    #+#             */
/*   Updated: 2025/05/28 19:29:42 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_lstadd_back_tail function adds a node to the end of the singly linked
 * list.
 * It uses the tail pointer of the list to avoid traversing the whole list.
 * The tail pointer is updated to point to the new node.
 *
 * @param lst     The address of the pointer to the first node of the list.
 * @param tail    The address of the pointer to the last node of the list.
 * @param new     The new node to be added to the list.
 *
 * @return        No return value.
 *
 */
void	ft_lstadd_back_tail(t_list **lst, t_list **tail, t_list *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		(*tail)->next = new;
	*tail = new;
	return ;
}
