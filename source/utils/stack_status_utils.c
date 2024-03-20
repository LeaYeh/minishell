/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_status_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:54:50 by lyeh              #+#    #+#             */
/*   Updated: 2024/02/17 23:54:51 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_ast	*get_ast_from_stack(t_list *node)
{
	if (!node)
		return (NULL);
	return ((t_ast *)node->content);
}

void	print_parse_stack(t_list *node)
{
	while (node)
	{
		if (get_token_from_stack(node))
			printf("%d <- ", get_ast_from_stack(node)->type);
		node = node->next;
	}
	printf("(NULL)\n");
}
