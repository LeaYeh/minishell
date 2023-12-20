/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:29 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/20 19:11:51 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_lstpop function removes the first node from a singly linked list and
 * returns it - like popping a stack.
 *
 * @param lst    A double pointer to the first node of the list.
 *
 * @return       The removed node, or NULL if the list was empty.
 *
 */
t_list	*ft_lstpop(t_list **lst)
{
	t_list	*popped;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	popped = *lst;
	*lst = (*lst)->next;
	return (popped);
}
