/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:57:56 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/06 19:49:24 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "defines.h"

bool		set_next_pt_entry(t_pt_node **pt_entry,
				int state, int token_type, int action_mask);
bool		push_state(t_list **state_stack, int next_step);
bool		parse_shift(t_token *input_token,
				t_list **state_stack, t_list **parse_stack, int next_step);
bool		parse_reduce(t_list **state_stack,
				t_list **parse_stack, t_pt_node *pt_entry);
bool		parse_goto(t_list **state_stack, int token_type);

bool		init_parser_data(t_parser_data *parser_data, t_list *token_list);
void		free_parser_data(t_parser_data *parser_data);
bool		ft_parser(t_shell *shell);

/* Command table */
t_list_d	*build_cmd_table_list(t_list *token_list);
bool		handle_symbol_token(t_list **token_list, t_list_d **cmd_table_list);
bool		handle_word_token(t_list **token_list, t_list_d **cmd_table_list);
void		fill_subshell_level(t_list_d *cmd_table_list);

#endif
