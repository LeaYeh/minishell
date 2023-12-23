/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:38:17 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/23 19:10:07 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "defines.h"

bool	drop_num_stack(t_list **stack, int num, void (*del)(void *));
t_list	*pop_num_stack(t_list **stack, int num);

t_token	*init_token_node(int type, char *data);
void	free_token_node(void *content);

t_ast	*init_ast_node(int type, char *data, t_list *children);
void	free_ast_node(t_ast *ast);
void	free_ast_data(t_ast *ast);

char	*ft_get_token_type_str(int type);

int		get_state_from_stack(t_list *node);
t_token	*get_token_from_stack(t_list *node);
t_ast	*get_ast_from_stack(t_list *node);

int		get_token_type_from_list(t_list *token_list);
char	*get_token_data_from_list(t_list *token_list);
void	print_state_stack(t_list *stack);
void	print_parse_stack(t_list *stack);

void	print_token_list(t_list *token_list);

#endif
