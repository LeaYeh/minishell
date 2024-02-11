/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:35:12 by ldulling          #+#    #+#             */
/*   Updated: 2024/02/11 00:40:39 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup(t_list *lst, void *(*dup)(void *), void (*del)(void *))
{
	t_list	*cur;
	t_list	*new_lst;
	t_list	*new_lst_tail;
	t_list	*new_node;
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
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
			return (del(new_content), ft_lstclear(&new_lst, del), NULL);
		ft_lstadd_back_eff(&new_lst, &new_lst_tail, new_node);
		cur = cur->next;
	}
	return (new_lst);
}
