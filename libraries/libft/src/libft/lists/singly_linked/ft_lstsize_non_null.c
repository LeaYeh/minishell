/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_non_null.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:52:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/18 12:14:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_lstsize_non_null function counts the number of non-null content nodes
 * in a singly linked list.
 *
 * @param lst    A pointer to the first node of the list.
 *               If lst is NULL, the function returns 0.
 *
 * @return       The number of non-null content nodes in the list.
 *
 */
int	ft_lstsize_non_null(t_list *lst)
{
	int		n;
	t_list	*cur;

	n = 0;
	cur = lst;
	while (cur != NULL)
	{
		if (cur->content != NULL)
			n++;
		cur = cur->next;
	}
	return (n);
}
