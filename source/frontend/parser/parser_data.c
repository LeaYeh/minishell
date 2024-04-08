/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:05:05 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/08 12:27:27 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

bool	init_parser_data(t_prs_data *parser_data, t_list *token_list)
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

void	free_parser_data(t_prs_data *parser_data)
{
	if (!parser_data)
		return ;
	ft_lstclear(&parser_data->token_list, (void *)free_token);
	ft_lstclear(&parser_data->state_stack, NULL);
	ft_lstclear(&parser_data->parse_stack, (void *)free_ast_node);
}
