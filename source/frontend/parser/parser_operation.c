/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:52:51 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 17:55:58 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

bool	push_state(t_list **state_stack, int next_step)
{
	t_list	*node;
	int		*state;

	state = (int *)malloc(sizeof(int));
	if (!state)
		return (false);
	*state = next_step;
	node = ft_lstnew(state);
	if (!node)
		return (free(state), false);
	ft_lstadd_front(state_stack, node);
	return (true);
}

// convert the token into the ast_node and push it into the parse_stack
bool	push_node(t_list **parse_stack, t_ast *ast_node)
{
	t_list	*node;

	if (!ast_node)
		return (false);
	node = ft_lstnew(ast_node);
	if (!node)
		return (false);
	ft_lstadd_front(parse_stack, node);
	return (true);
}

bool	parse_shift(t_token *token_node,
	t_list **state_stack, t_list **parse_stack, int next_step)
{
	t_ast	*ast_node;

	ast_node = init_ast_node(token_node->type, token_node->data, NULL);
	free(token_node);
	if (!ast_node)
		return (false);
	if (!push_node(parse_stack, ast_node))
		return (free_ast_node(ast_node), false);
	if (!push_state(state_stack, next_step))
		return (false);
	return (true);
}

bool	parse_reduce(
	t_list **state_stack, t_list **parse_stack, t_pt_node *pt_entry)
{
	t_list	*children;
	t_ast	*reduce_node;

	reduce_node = init_ast_node(pt_entry->next_state, NULL, NULL);
	if (!reduce_node)
		return (false);
	if (!drop_num_stack(state_stack, pt_entry->num_reduced, free))
		return (free_ast_node(reduce_node), false);
	children = pop_num_stack(parse_stack, pt_entry->num_reduced);
	if (!children)
		return (free_ast_node(reduce_node), false);
	ft_lstadd_back(&reduce_node->children, children);
	if (!push_node(parse_stack, reduce_node))
		return (free_ast_node(reduce_node), false);
	return (true);
}

bool	parse_goto(t_list **state_stack, int token_type)
{
	t_pt_node	*pt_entry;

	pt_entry = NULL;
	if (!set_next_pt_entry(&pt_entry,
			get_state_from_stack(*state_stack),
			token_type,
			A_GOTO))
		return (false);
	if (!pt_entry)
		return (true);
	if (!push_state(state_stack, pt_entry->next_state))
		return (free(pt_entry), false);
	return (free(pt_entry), true);
}
