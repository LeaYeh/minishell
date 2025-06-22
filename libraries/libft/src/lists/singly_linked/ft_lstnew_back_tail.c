/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_back_tail.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:11:17 by ldulling          #+#    #+#             */
/*   Updated: 2025/05/28 20:24:43 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_lstnew_back_tail function creates a new node with the provided content
 * and adds it to the end of the singly linked list.
 * It uses the tail pointer of the list to avoid traversing the whole list.
 * The tail pointer is updated to point to the new node.
 *
 * @param lst        The address of the list to add the new node to.
 * @param tail       The address of the pointer to the last node of the list.
 *                   If tail (not *tail) is NULL, it is ignored.
 * @param content    The content to be added to the new node.
 *
 * @return           Returns true if the new node was successfully added, false
 *                   if malloc failed or lst (not *lst) is NULL.
 *
 */
bool	ft_lstnew_back_tail(t_list **lst, t_list **tail, void *content)
{
	t_list	*new_node;

	if (lst == NULL || tail == NULL)
		return (ft_lstnew_back(lst, content));
	new_node = ft_lstnew(content);
	if (new_node == NULL)
		return (false);
	ft_lstadd_back_tail(lst, tail, new_node);
	return (true);
}
