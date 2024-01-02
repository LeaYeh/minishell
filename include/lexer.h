/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:35:51 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/02 14:16:46 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "defines.h"

/* create_token_list.c */
bool	create_token_list(t_list **token_list, t_list **token_data_list);
bool	separate_operators(t_list *lst_node, size_t i);
bool	split_and_advance_node(t_list **lst_node, char **token_data, size_t *i);
bool	add_end_node(t_list	**token_list);

/* finetune_token_list.c */
void	finetune_token_list(t_list *token_list);
void	adjust_assignment_word_tokens(t_list *token_list);

/* get_token_data_list.c */
t_list	*get_token_data_list(char *input_line);
char	*get_token_data(char *input_line, size_t *i);

/* lexer.c */
bool	ft_lexer(t_shell *shell);

/* lexer_utils.c */
void	skip_operator(char *token_data, size_t *i);
bool	split_token_node(t_list *lst_node1, size_t i);

/* set_token_type.c */
void	set_token_type(t_list *lst_node);
int		which_lesser(char *token_data);
int		which_greater(char *token_data);
int		which_pipe(char *token_data);
bool	is_assignment_word(char *str);

#endif
