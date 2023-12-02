/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:12 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/24 23:30:53 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Does not mark the new node as the end of the list by itself.
 */

#include "libft.h"

void	ft_lstadd_back_d(t_list_d **lst, t_list_d *new)
{
	t_list_d	*cur;

	if (lst != NULL && new != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			cur = *lst;
			while (cur->next != NULL)
				cur = cur->next;
			cur->next = new;
			new->prev = cur;
		}
	}
	return ;
}
