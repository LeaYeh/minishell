/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:05:05 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 17:11:03 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

bool	init_parser_data(t_parser_data *parser_data, t_list *token_list)
{
	parser_data->token_list = dup_token_list(token_list);
	if (!parser_data->token_list)
		return (false);
	parser_data->state_stack = NULL;
	parser_data->parse_stack = NULL;
	if (!push_state(&parser_data->state_stack, 0))
		return (false);
	return (true);
}

void	free_parser_data(t_parser_data *parser_data)
{
	ft_lstclear(&parser_data->token_list, (void *)free_token_node);
	ft_lstclear(&parser_data->state_stack, free);
	ft_lstclear(&parser_data->parse_stack, (void *)free_ast_node);
}
