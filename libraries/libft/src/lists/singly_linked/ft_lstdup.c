/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:35:12 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/07 19:09:20 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_lstdup function duplicates a singly linked list by creating new nodes
 * with the same content as the original list. The content of the new nodes is
 * created by calling the provided 'dup' function on the content of the original
 * nodes.
 *
 * @param lst    The original list to be duplicated.
 * @param dup    The function to duplicate the content of the nodes.
 * @param del    The function to delete the content of the nodes in case of
 *               failure.
 *
 * @return       Returns a pointer to the first node of the new list, or NULL if
 *               the list could not be duplicated.
 *
 */
t_list	*ft_lstdup(t_list *lst, void *(*dup)(void *), void (*del)(void *))
{
	t_list	*cur;
	t_list	*new_lst;
	t_list	*new_lst_tail;
	void	*new_content;

	if (lst == NULL || dup == NULL || del == NULL)
		return (NULL);
	new_lst = NULL;
	new_lst_tail = NULL;
	cur = lst;
	while (cur != NULL)
	{
		new_content = (*dup)(cur->content);
		if (new_content == NULL)
			return (ft_lstclear(&new_lst, del), NULL);
		if (!ft_lstnew_back_eff(&new_lst, &new_lst_tail, new_content))
			return (del(new_content), ft_lstclear(&new_lst, del), NULL);
		cur = cur->next;
	}
	return (new_lst);
}
