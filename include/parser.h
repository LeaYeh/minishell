/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:57:56 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/08 18:03:38 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "defines.h"

void		report_syntax_error(t_sh *shell, t_prs_data *parser_data);

bool		set_next_pt_entry(
				t_pt_node **pt_entry,
				int state,
				t_prs_elem element,
				t_prs_act action_mask);
bool		push_state(t_list **state_stack, int state);
bool		parse_shift(
				t_tok *token,
				t_list **state_stack,
				t_list **parse_stack,
				int next_state);
bool		parse_reduce(
				t_list **state_stack,
				t_list **parse_stack,
				t_pt_node *pt_entry);
bool		parse_goto(t_list **state_stack, t_prs_elem element);

bool		init_parser_data(t_prs_data *parser_data, t_list *token_list);
void		free_parser_data(t_prs_data *parser_data);
bool		parser(t_sh *shell);

/* Command table */
t_list_d	*build_cmd_table_list(t_list *token_list);
bool		handle_symbol_token(t_list **token_list, t_list_d **cmd_table_list);
bool		handle_word_token(t_list **token_list, t_list_d **cmd_table_list);

/* cmd table symbol utils */
bool		fill_redirect_by_scenario(
				t_list **token_list, t_list_d **cmd_table_list);
void		fill_control_op(t_list **token_list, t_list_d **cmd_table_list);
void		fill_parenthesis(t_list **token_list, t_list_d **cmd_table_list);

#endif
