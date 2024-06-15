/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:35:51 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/08 12:44:36 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "defines.h"

/* lexer.c */
bool	lexer(t_sh *shell);

/* lexer_utils.c */
bool	is_operator(char *token_data);
void	print_missing_pair_error(char *str);
void	skip_operator(char *token_data, int *i);
bool	split_token_node(t_list *node_front, int i);

/* token_data_list.c */
bool	create_token_data_list(t_list **token_data_list, char *input_line);

/* token_list.c */
bool	create_token_list(t_list **token_list, t_list **token_data_list);
bool	append_end_node(t_list	**token_list);

/* token_list_post_processing.c */
void	finetune_token_list(t_list *token_list);

/* token_type.c */
void	set_token_type(t_list *token_list);

#endif
