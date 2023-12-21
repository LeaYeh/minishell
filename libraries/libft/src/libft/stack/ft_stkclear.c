/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stkclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:03:00 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/21 13:00:37 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stkclear(t_stack **stk, void (*del)(void *))
{
	t_stack	*cur;

	while (stk && *stk != NULL)
	{
		cur = *stk;
		*stk = (*stk)->next;
		if (*del)
			(*del)(cur->content);
		free(cur);
	}
	return ;
}
