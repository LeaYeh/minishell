/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:38:17 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/28 19:59:15 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "defines.h"

/* Token list utils */
t_token		*init_token_node(int type, char *data);
void		free_token_node(t_token *token);
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

/* Type utils */
char		*ft_get_token_type_str(int type);
bool		is_control_op(int token_type);
bool		is_identifier(int token_type);
bool		is_rule(int token_type);
bool		is_io_redirect_op(int token_type);

/* Stack utils */
int			get_state_from_stack(t_list *node);
t_token		*get_token_from_stack(t_list *node);
t_ast		*get_ast_from_stack(t_list *node);
void		print_state_stack(t_list *stack);
void		print_parse_stack(t_list *stack);
bool		drop_num_stack(t_list **stack, int num, void (*del)(void *));
t_list		*pop_num_stack(t_list **stack, int num);

#endif
