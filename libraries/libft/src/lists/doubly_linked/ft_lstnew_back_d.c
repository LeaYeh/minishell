/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_back_d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:30:19 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/20 12:40:06 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_lstnew_back_d function creates a new node with the provided content
 * and adds it to the end of the doubly linked list.
 *
 * @param lst        The address of the list to add the new node to.
 * @param content    The content to be added to the new node.
 *
 * @return           Returns true if the new node was successfully added, false
 *                   if malloc failed.
 *
 */
bool	ft_lstnew_back_d(t_list_d **lst, void *content)
{
	t_list_d	*new_node;

	new_node = ft_lstnew_d(content);
	if (new_node == NULL)
		return (false);
	ft_lstadd_back_d(lst, new_node);
	return (true);
}
