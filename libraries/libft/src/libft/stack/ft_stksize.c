/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stksize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:04:09 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/11 21:05:09 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stksize(t_stack *stk)
{
	int		n;
	t_stack	*cur;

	if (stk == NULL)
		return (0);
	n = 0;
	cur = stk;
	while (cur != NULL)
	{
		cur = cur->next;
		n++;
	}
	return (n);
}
