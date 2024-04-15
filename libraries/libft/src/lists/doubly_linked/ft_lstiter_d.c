/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:35:04 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/21 21:36:34 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter_d(t_list_d *lst, void (*f)(void *))
{
	t_list_d	*cur;

	if (lst == NULL || f == NULL)
		return ;
	cur = lst;
	while (cur != NULL)
	{
		(*f)(cur->content);
		cur = cur->next;
	}
	return ;
}
