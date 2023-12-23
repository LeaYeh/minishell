/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_front_content.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:29 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/23 21:00:58 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_lstpop_front_content function removes and frees the first node from a
 * singly linked list and returns its content - like popping a stack.
 *
 * @param lst    A double pointer to the first node of the list.
 *
 * @return       The content of the removed node, or NULL if the list was empty.
 *
 */
void	*ft_lstpop_front_content(t_list **lst)
{
	void	*popped_content;
	t_list	*popped_node;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	popped_node = *lst;
	popped_content = popped_node->content;
	*lst = (*lst)->next;
	free(popped_node);
	return (popped_content);
}
