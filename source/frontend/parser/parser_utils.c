/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:05:05 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/17 21:37:01 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

bool	init_parse(t_stack **state_stack, t_stack **parse_stack)
{
	*parse_stack = NULL;
	if (!push_state(state_stack, 0))
		return (false);
	return (true);
}

void	free_parse(t_stack **state_stack, t_stack **parse_stack)
{
	ft_stkclear(state_stack, free);
	ft_stkclear(parse_stack, free_token_node);
}
