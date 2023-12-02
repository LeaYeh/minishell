/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort_bubble.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:16:52 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/27 10:36:43 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap_head(t_list **lst);
static bool	bubble_sort(t_list **lst, void *(*cmp)(void *, void *));

void	ft_lstsort_bubble(t_list **lst, void *(*cmp)(void *, void *))
{
	bool	is_sorted;

	if (lst != NULL && *lst != NULL && (*lst)->next != NULL && cmp != NULL)
	{
		is_sorted = false;
		while (is_sorted != true)
		{
			if (!(*cmp)((*lst)->content, (*lst)->next->content))
				swap_head(lst);
			is_sorted = bubble_sort(lst, cmp);
		}
	}
	return ;
}

static void	swap_head(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst)->next;
	(*lst)->next = tmp->next;
	tmp->next = *lst;
	*lst = tmp;
}

static bool	bubble_sort(t_list **lst, void *(*cmp)(void *, void *))
{
	t_list	*cur;
	t_list	*prev;
	t_list	*tmp;
	bool	is_sorted;

	cur = (*lst)->next;
	prev = *lst;
	is_sorted = true;
	while (cur->next)
	{
		if (!(*cmp)(cur->content, cur->next->content))
		{
			tmp = cur->next;
			cur->next = tmp->next;
			tmp->next = cur;
			prev->next = tmp;
			is_sorted = false;
		}
		else
			cur = cur->next;
		prev = prev->next;
	}
	return (is_sorted);
}
