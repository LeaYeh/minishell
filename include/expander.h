/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:25:46 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/27 22:07:39 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "defines.h"

/* bad_substitution.c */
bool	is_bad_substitution(char *str, t_expander_op op_mask);

/* expand_special_param.c */
bool	expand_exit_code(char **str, size_t *i, int exit_code);

/* expand_variable.c */
bool	expand_variable(char **str, size_t *i, size_t offset, t_list *env_list);
size_t	count_var_len(char *str);

/* expander.c */
int		ft_expander(char *str, t_list **lst, t_shell *shell, \
					t_expander_op op_mask);

/* expander_utils.c */
size_t	count_offset(char *str);
size_t	count_replace_len(char *str);
bool	is_open_pair(unsigned char c, t_is_open_pair_op operation);
void	skip_to_dollar(char *str, size_t *i);
void	skip_to_dollar_not_in_single_quotes(char *str, size_t *i);

/* parameter_expansion.c */
bool	handle_parameter_expansion(char **str, t_list **lst, t_shell *shell, \
									t_expander_op op_mask);
bool	expand(char **str, size_t *i, t_shell *shell, t_expander_op op_mask);
bool	handle_dollar_quotes(char **str, size_t *i);

/* remove_quotes.c */
bool	handle_remove_quotes(t_list **lst);
bool	remove_quotes(char **str);

#endif
