/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:38:17 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/03 14:29:24 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "defines.h"

/* Token list utils */
t_token		*init_token_node(int type, char *data);
void		free_token_node(t_token *token);
t_token		*get_token_from_list(t_list *token_list);
int			get_token_type_from_list(t_list *token_list);
char		*get_token_data_from_list(t_list *token_list);
void		print_token_list(t_list *token_list);
t_token		*dup_token_node(t_token *token);
t_list		*dup_token_list(t_list *token_list);

/* AST utils */
t_ast		*init_ast_node(int type, char *data, t_list *children);
void		free_ast_node(t_ast *ast);
void		free_ast_data(t_ast *ast);

/* Redirect utils */
t_io_red	*init_io_red(void);
void		free_io_red(t_io_red *io_red);

/* Cmd table utils */
t_cmd_table	*init_cmd_table(void);
void		free_cmd_table(t_cmd_table *cmd_table);
t_cmd_table	*get_last_simple_cmd_table(t_list_d *cmd_table_list);
bool		append_empty_cmd_table(t_list_d **cmd_table_list);
bool		append_cmd_table_by_scenario(
				int token_type, t_list_d **cmd_table_list);

/* Type utils */
char		*ft_get_token_type_str(int type);
bool		is_control_op(int token_type);
bool		is_io_red_op(int token_type);
bool		is_word(int token_type);
bool		is_subshell_symbol(int token_type);
// bool		is_identifier(int token_type);
// bool		is_rule(int token_type);

/* File utils */
char		*generate_tmp_filename(int cmdtable_id, char *category);
bool		remove_file(char **filename);
bool		append_line_to_file(char *line, char *filename);

/* Stack utils */
int			get_state_from_stack(t_list *node);
t_token		*get_token_from_stack(t_list *node);
t_ast		*get_ast_from_stack(t_list *node);
void		print_state_stack(t_list *stack);
void		print_parse_stack(t_list *stack);
bool		drop_num_stack(t_list **stack, int num, void (*del)(void *));
t_list		*pop_num_stack(t_list **stack, int num);

/* String utils */
bool	is_valid_varname(char c);
bool	is_valid_varname_start(char c);
bool	skip_to_same_quote(char *str, size_t *i);

#endif
