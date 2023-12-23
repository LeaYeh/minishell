/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:22 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/23 14:25:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_d(t_list_d **lst, void (*del)(void *))
{
	t_list_d	*cur;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		cur = *lst;
		*lst = (*lst)->next;
		ft_lstdelone_d(cur, del);
	}
	return ;
}
