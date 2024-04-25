/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:35 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/23 11:43:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	lstadd_back_eff(t_list **head, t_list **tail, t_list **new_node);

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cur;
	t_list	*new_lst;
	t_list	*new_lst_tail;
	t_list	*new_node;
	void	*new_content;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new_lst = NULL;
	new_lst_tail = NULL;
	cur = lst;
	while (cur != NULL)
	{
		new_content = (*f)(cur->content);
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			del(new_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		lstadd_back_eff(&new_lst, &new_lst_tail, &new_node);
		cur = cur->next;
	}
	return (new_lst);
}

static void	lstadd_back_eff(t_list **head, t_list **tail, t_list **new_node)
{
	if (*head == NULL)
		*head = *new_node;
	else
		(*tail)->next = *new_node;
	*tail = *new_node;
	return ;
}
