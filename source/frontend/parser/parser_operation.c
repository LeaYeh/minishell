/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:52:51 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/19 20:49:00 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

bool	push_state(t_stack **state_stack, int next_step)
{
	t_stack	*node;
	int		*tmp;

	tmp = malloc(sizeof(int));
	if (!tmp)
		return (false);
	*tmp = next_step;
	node = ft_stknew((void *)tmp);
	if (!node)
		return (false);
	ft_stkpush(state_stack, node);
	return (true);
}

bool	push_token(t_stack **parse_stack, t_token *token)
{
	t_stack	*node;

	node = ft_stknew(token);
	if (!node)
		return (false);
	ft_stkpush(parse_stack, node);
	return (true);
}

bool	parse_shift(t_token *input_token,
	t_stack **state_stack, t_stack **parse_stack, int next_step)
{
	if (!push_token(parse_stack, input_token))
		return (free_token_node(input_token), false);
	if (!push_state(state_stack, next_step))
		return (false);
	printf("After shift:\n");
	printf("state_stack: ");
	print_state_stack(ft_stkpeektop(*state_stack));
	printf("parse_stack: ");
	print_parse_stack(ft_stkpeektop(*parse_stack));
	return (true);
}

bool	parse_reduce(
	t_stack **state_stack, t_stack **parse_stack, t_pt_node *pt_entry)
{
	t_token	*reduction_node;

	reduction_node = init_token_node(pt_entry->next_state, NULL);
	if (!reduction_node)
		return (false);
	if (!drop_num_stack(state_stack, pt_entry->num_reduced, free) || \
		!drop_num_stack(parse_stack, pt_entry->num_reduced, free_token_node))
		return (false);
	if (!push_token(parse_stack, reduction_node))
		return (false);
	printf("reduction_node->type: %d\n", reduction_node->type);
	printf("state_stack: ");
	print_state_stack(ft_stkpeektop(*state_stack));
	printf("parse_stack: ");
	print_parse_stack(ft_stkpeektop(*parse_stack));
	return (true);
}

bool	parse_goto(t_stack **state_stack, int token_type)
{
	t_pt_node	*pt_entry;

	pt_entry = get_next_pt_entry(
			get_state_from_stack(ft_stkpeektop(*state_stack)),
			token_type,
			A_GOTO);
	if (!pt_entry)
		return (false);
	if (!push_state(state_stack, pt_entry->next_state))
		return (free(pt_entry), false);
	printf("After goto:\n");
	printf("state_stack: ");
	print_state_stack(ft_stkpeektop(*state_stack));
	return (free(pt_entry), true);
}
