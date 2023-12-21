/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stkpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:07:28 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/11 21:08:22 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_stkpop(t_stack **stk)
{
	t_stack	*top;

	if (stk != NULL && *stk != NULL)
	{
		top = *stk;
		*stk = (*stk)->next;
		top->next = NULL;
		return (top);
	}
	return (NULL);
}
