/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stkdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:41:12 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/17 22:13:23 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stkdelone(t_stack *stk, void (*del)(void *))
{
	if (stk != NULL)
	{
		if (del != NULL && stk->content != NULL)
			(*del)(stk->content);
		free(stk);
	}
	return ;
}
