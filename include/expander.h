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

/* expander_task_stack.c */
bool	create_expander_task_stack(t_list **task_stack, char *new_str, \
									t_expander_op op_mask);

/* expand_special_param.c */
bool	expand_exit_code(char **new_str, t_expander_task *task, int exit_code);

/* expand_variable.c */
bool	expand_variable(char **new_str, t_expander_task *task, \
						t_list *env_list);
size_t	get_varname_len(char *str);

/* expand.c */
bool	expand(char **new_str, t_list **lst, t_shell *shell, \
				t_expander_op op_mask);
bool	execute_expander_task_stack(char **new_str, t_list *task_stack, \
									t_list **lst, t_shell *shell);
bool	is_null_expansion(char *dup, t_list *task_stack);

/* expander.c */
int		ft_expander(char *str, t_list **lst, t_shell *shell, \
					t_expander_op op_mask);

/* expander_utils.c */
size_t	get_offset(char *str);
size_t	get_replace_len(char *str);
bool	is_open_pair(unsigned char c, t_is_open_pair_op operation);
void	skip_to_dollar_not_in_single_quotes(char *str, size_t *i);
void	skip_to_expander_symbol(char *str, size_t *i);

/* remove_quotes.c */
bool	remove_quote(char **new_str, t_expander_task *task);

#endif
