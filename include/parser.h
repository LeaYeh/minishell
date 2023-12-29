/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:57:56 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/29 21:12:48 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "defines.h"

t_pt_node	*get_next_pt_entry(int state, int token_type, int action);

bool		push_state(t_list **state_stack, int next_step);
bool		push_token(t_list **parse_stack, t_ast *ast_node);
bool		parse_shift(t_token *input_token,
				t_list **state_stack, t_list **parse_stack, int next_step);
bool		parse_reduce(t_list **state_stack,
				t_list **parse_stack, t_pt_node *pt_entry);
bool		parse_goto(t_list **state_stack, int token_type);

bool		init_parse(t_list **state_stack, t_list **parse_stack);
void		free_parse(t_list **state_stack, t_list **parse_stack);
bool		ft_parse(t_shell *shell);

/* Command table */
t_list_d	*build_cmd_table_list(t_list *token_list);
bool		handle_symbol_token(t_list **token_list, t_list_d **cmd_table_list);
bool		handle_word_token(t_list **token_list, t_list_d **cmd_table_list);

#endif
