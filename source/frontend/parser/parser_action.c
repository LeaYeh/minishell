/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:52:51 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/08 18:04:31 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static bool	push_node(t_list **parse_stack, t_ast *ast_node);

bool	parse_shift(
			t_tok *token,
			t_list **state_stack,
			t_list **parse_stack,
			int next_state)
{
	t_ast	*ast_node;

	ast_node = init_ast_node((t_prs_elem)token->type, token->data, NULL);
	free(token);
	if (!ast_node)
		return (false);
	if (!push_node(parse_stack, ast_node))
		return (free_ast_node(ast_node), false);
	if (!push_state(state_stack, next_state))
		return (false);
	return (true);
}

bool	parse_reduce(
			t_list **state_stack,
			t_list **parse_stack,
			t_pt_node *pt_entry)
{
	t_list	*children;
	t_ast	*reduce_node;

	reduce_node = init_ast_node((t_prs_elem)pt_entry->next_state, NULL, NULL);
	if (!reduce_node)
		return (false);
	if (!drop_num_stack(state_stack, pt_entry->num_reduced, NULL))
		return (free_ast_node(reduce_node), false);
	children = pop_num_stack(parse_stack, pt_entry->num_reduced);
	if (!children)
		return (free_ast_node(reduce_node), false);
	ft_lstadd_back(&reduce_node->children, children);
	if (!push_node(parse_stack, reduce_node))
		return (free_ast_node(reduce_node), false);
	return (true);
}

bool	parse_goto(t_list **state_stack, t_prs_elem element)
{
	t_pt_node	*pt_entry;

	pt_entry = NULL;
	if (!set_next_pt_entry(&pt_entry,
			get_state_from_stack(*state_stack), element, A_GOTO))
		return (false);
	if (!pt_entry)
		return (true);
	if (!push_state(state_stack, pt_entry->next_state))
		return (free(pt_entry), false);
	return (free(pt_entry), true);
}

bool	push_state(t_list **state_stack, int state)
{
	return (ft_lstnew_front(state_stack, (void *)(long)state));
}

/**
 * Convert the token into the ast_node and push it onto the parse_stack
 */
static bool	push_node(t_list **parse_stack, t_ast *ast_node)
{
	if (!ast_node)
		return (false);
	return (ft_lstnew_front(parse_stack, ast_node));
}
