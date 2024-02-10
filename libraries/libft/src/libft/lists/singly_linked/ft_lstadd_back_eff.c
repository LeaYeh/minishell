/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_eff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 00:35:15 by ldulling          #+#    #+#             */
/*   Updated: 2024/02/11 00:41:20 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back_eff(t_list **lst, t_list **tail, t_list *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		(*tail)->next = new;
	*tail = new;
	return ;
}
