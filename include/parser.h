/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:57:56 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/17 13:41:27 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "defines.h"

bool		push_state(t_stack **state_stack, int next_step);
bool		push_token(t_stack **parse_stack, t_token *token);
bool		parse_shift(t_list **input_buffer,
				t_stack **state_stack, t_stack **parse_stack, int next_step);
bool		parse_reduce(t_stack **state_stack,
				t_stack **parse_stack, t_pt_node *pt_entry);
bool		parse_goto(t_pt_node *pt_entry, t_stack **state_stack);

t_pt_node	*get_pt_entry(const int parsing_table[][5],
				int state, int token_type);
t_pt_node	*find_pt_entry(int state, int token_type);
bool		update_pt_entry(t_pt_node **pt_entry, int state, int token_type);

bool		init_parse(t_list *token_list, t_list **input_buffer,
				t_stack **state_stack, t_stack **parse_stack);
void		free_parse(t_stack **state_stack, t_stack **parse_stack);

#endif
