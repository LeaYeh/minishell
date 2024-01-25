/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:09:14 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/25 16:09:17 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_lstnew_front function creates a new node with the provided content and
 * adds it to the beginning of the singly linked list.
 *
 * @param lst     The address of the list to add the new node to.
 * @param content The content to be added to the new node.
 *
 * @return        Returns true if the new node was successfully added, false if
 *                malloc failed.
 *
 */
bool	ft_lstnew_front(t_list **lst, void *content)
{
	t_list	*new_node;

	new_node = ft_lstnew(content);
	if (new_node == NULL)
		return (false);
	ft_lstadd_front(lst, new_node);
	return (true);
}
