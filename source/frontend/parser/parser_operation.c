/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:52:51 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/23 16:08:09 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

bool	push_state(t_list **state_stack, int next_step)
{
	t_list	*node;
	int		*tmp;

	tmp = malloc(sizeof(int));
	if (!tmp)
		return (false);
	*tmp = next_step;
	node = ft_lstnew((void *)tmp);
	if (!node)
		return (free(tmp), false);
	ft_lstadd_front(state_stack, node);
	return (true);
}

bool	push_token(t_list **parse_stack, t_token *token)
{
	t_list	*node;

	node = ft_lstnew(token);
	if (!node)
		return (false);
	ft_lstadd_front(parse_stack, node);
	return (true);
}

bool	parse_shift(t_token *input_token,
	t_list **state_stack, t_list **parse_stack, int next_step)
{
	if (!push_token(parse_stack, input_token))
		return (free_token_node(input_token), false);
	if (!push_state(state_stack, next_step))
		return (false);
	printf("After shift:\n");
	printf("state_stack: ");
	print_state_stack(*state_stack);
	printf("parse_stack: ");
	print_parse_stack(*parse_stack);
	return (true);
}

bool	parse_reduce(
	t_list **state_stack, t_list **parse_stack, t_pt_node *pt_entry)
{
	t_token	*reduction_node;

	reduction_node = init_token_node(pt_entry->next_state, NULL);
	if (!reduction_node)
		return (false);
	if (!drop_num_stack(state_stack, pt_entry->num_reduced, free) || \
		!drop_num_stack(parse_stack, pt_entry->num_reduced, free_token_node))
		return (free_token_node(reduction_node), false);
	if (!push_token(parse_stack, reduction_node))
		return (free_token_node(reduction_node), false);
	printf("reduction_node->type: %d\n", reduction_node->type);
	printf("state_stack: ");
	print_state_stack(*state_stack);
	printf("parse_stack: ");
	print_parse_stack(*parse_stack);
	return (true);
}

bool	parse_goto(t_list **state_stack, int token_type)
{
	t_pt_node	*pt_entry;

	pt_entry = get_next_pt_entry(
			get_state_from_stack(*state_stack),
			token_type,
			A_GOTO);
	if (!pt_entry)
		return (false);
	if (!push_state(state_stack, pt_entry->next_state))
		return (free(pt_entry), false);
	printf("After goto:\n");
	printf("state_stack: ");
	print_state_stack(*state_stack);
	return (free(pt_entry), true);
}
