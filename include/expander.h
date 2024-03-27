/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:25:46 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/25 18:44:19 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "defines.h"

/* bad_substitution.c */
bool			is_bad_substitution(char *str, t_expander_op op_mask);

/* expander.c */
int				expander(char *str, t_list **lst, t_shell *shell,
					t_expander_op op_mask);

/* expander_task_list.c */
bool			set_expander_task_list(t_list **task_list, char **base_str,
					t_expander_op op_mask);
bool			append_quote_task(
					t_list **task_list, char **base_str, int *i);
bool			append_parameter_task(t_list **task_list, char **base_str,
					int *i, t_expander_op op_mask);

/* expander_task_list_utils.c */
void			free_expander_task(t_expander_task *task);
char			*get_varname(char *str);
int				get_varname_len(char *str);
t_expander_task	*init_expander_task(t_expander_task_type type, int start,
					int replace_len, char *str);
void			update_expander_tasks(t_list *task_list, int diff,
					char **new_base_str);

/* expander_utils.c */
int				get_offset(char *str);
int				get_replace_len(char *str);
void			skip_to_dollar_not_in_single_quotes(char *str, int *i);

/* expansion_handler.c */
bool			handle_expansion(t_list **lst, t_shell *shell,
					t_expander_op op_mask);
bool			handle_parameter_expansion(t_list *task_list, t_shell *shell);
bool			set_expanded_list(t_list **lst, t_expander_op op_mask,
					t_list **task_list);

/* null_expansion.c */
void			drop_null_expansion_nodes(t_list **lst);

/* quote_removal.c */
bool			handle_quote_removal(t_list *task_list);
bool			remove_quote(t_list *task_list);

/* special_param_expansion.c */
bool			expand_exit_code(t_list *task_list, int exit_code);

/* variable_expansion.c */
bool			expand_variable(t_list *task_list, t_list *env_list);

/* wildcard_expansion.c */
bool			handle_wildcard_expansion(t_list **lst);

/* word_splitting.c */
bool			handle_word_splitting(t_list *lst, t_list **task_list);

/* word_splitting_utils.c */
char			*split_base_str(char **base_str, int *i, int *end);
int				trim_front_whitespace(char **base_str, int *i, int *end);
bool			append_rest_to_list(t_list **lst, t_list *task_list,
					char *rest, int trimmed_len);

#endif
