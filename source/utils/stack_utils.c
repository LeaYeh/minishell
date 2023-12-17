/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:55:34 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/16 21:56:09 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

bool	drop_num_stack(t_stack **stack, int num)
{
	int		i;
	t_stack	*node;

	i = 0;
	while (i < num)
	{
		node = ft_stkpop(stack);
		if (!node)
			return (false);
		free(node);
		i++;
	}
	return (true);
}
