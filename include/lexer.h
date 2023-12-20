/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:35:51 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/20 12:06:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "defines.h"

/* create_token_list.c */
bool	create_token_list(t_list **token_list, t_list **data_list);
bool	separate_operators(t_list *lst_node, size_t i);
bool	add_end_node(t_list	**token_list);

/* get_data.c */
bool	get_data_list(t_list **data_list, char *input_line);
char	*get_data(char *input_line, size_t *i);

/* get_type.c */
void	get_type(t_list *lst_node);
int		which_lesser(char *data);
int		which_greater(char *data);
int		which_pipe(char *data);
bool	is_assignment_word(char *str);

/* lexer.c */
bool	ft_lexer(t_shell *shell);

/* lexer_utils.c */
void	skip_operator(char *data, size_t *i);
void	skip_past_same_quote(char *str, size_t *i);
bool	split_node(t_list *lst_node1, size_t i);

#endif
