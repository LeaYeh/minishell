/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort_bubble.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:16:52 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/23 11:55:40 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	bubble_sort(t_list **lst, void *(*cmp)(void *, void *));

void	ft_lstsort_bubble(t_list **lst, void *(*cmp)(void *, void *))
{
	bool	is_sorted;

	if (lst == NULL || *lst == NULL || (*lst)->next == NULL || cmp == NULL)
		return ;
	is_sorted = false;
	while (is_sorted != true)
	{
		if (!(*cmp)((*lst)->content, (*lst)->next->content))
			ft_lstswap_head(lst);
		is_sorted = bubble_sort(lst, cmp);
	}
	return ;
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
