/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:05:05 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/23 15:41:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

bool	init_parse(t_list **state_stack, t_list **parse_stack)
{
	*state_stack = NULL;
	*parse_stack = NULL;
	if (!push_state(state_stack, 0))
		return (false);
	return (true);
}

void	free_parse(t_list **state_stack, t_list **parse_stack)
{
	ft_lstclear(state_stack, free);
	ft_lstclear(parse_stack, free_token_node);
}
