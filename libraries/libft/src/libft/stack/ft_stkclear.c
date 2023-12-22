/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stkclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:03:00 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/22 19:53:22 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stkclear(t_list **stk, void (*del)(void *))
{
	t_list	*cur;

	if (stk == NULL)
		return ;
	while (*stk != NULL)
	{
		cur = *stk;
		*stk = (*stk)->next;
		if (*del)
			(*del)(cur->content);
		free(cur);
	}
	return ;
}
