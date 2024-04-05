/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:17:40 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 18:17:41 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static bool	is_null_expansion(char *str);

void	drop_null_expansion_nodes(t_list **expanded_list)
{
	t_list	*cur;

	cur = *expanded_list;
	while (cur)
	{
		if (is_null_expansion(cur->content))
			ft_lstdrop_node(expanded_list, &cur, free);
		else
			cur = cur->next;
	}
}

static bool	is_null_expansion(char *str)
{
	if (!str || !*str)
		return (true);
	return (false);
}
