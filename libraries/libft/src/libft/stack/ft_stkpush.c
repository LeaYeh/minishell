/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stkpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:05:44 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/22 19:54:53 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stkpush(t_list **stk, t_list *new)
{
	if (stk != NULL && new != NULL)
	{
		if (*stk == NULL)
			*stk = new;
		else
		{
			new->next = *stk;
			*stk = new;
		}
	}
	return ;
}
