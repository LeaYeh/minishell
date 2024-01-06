/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_expanded_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:07:52 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/06 01:10:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	create_expanded_list(t_list **lst, char *dup)
{
	t_list	*node;

	node = ft_lstnew(dup);
	if (!node)
		return (false);
	ft_lstadd_back(lst, node);
	return (true);
}
