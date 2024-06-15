/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:25:46 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/01 02:05:23 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "defines.h"

/* bad_substitution.c */
bool		is_bad_substitution(char *str, t_expd_op op_mask);

/* expander.c */
int			expander(
				char *str,
				t_list **expanded_list,
				t_sh *shell,
				t_expd_op op_mask);

/* expander_task_list.c */
bool		set_expander_task_list(
				t_list **task_list, char **base_str, t_expd_op op_mask);

/* expander_task_list_utils.c */
bool		any_task_of_type(t_list *task_list, t_expd_tsk_typ type);
void		drop_task_types(
				t_list **task_list, char **word, t_expd_tsk_typ type);
t_list		*get_expander_task_node(
				t_list *task_list, char **base_str, int i, t_expd_tsk_typ type);
void		update_expander_tasks(
				t_list *task_list, int diff, char **new_base_str);

/* expander_task_utils.c */
void		free_expander_task(t_expd_tsk *task);
t_expd_tsk	*init_expander_task(
				t_expd_tsk_typ type, int start, int replace_len, char *str);

/* expander_utils.c */
int			get_offset(char *str);
int			get_replace_len(char *str);
bool		is_unquoted_quote(char quote);
void		skip_to_dollar_not_in_single_quotes(char *str, int *i);

/* null_expansion.c */
void		drop_null_expansion_nodes(t_list **expanded_list);

/* parameter_expansion.c */
bool		handle_parameter_expansion(t_list **task_list, t_sh *shell);

/* quote_removal.c */
bool		handle_quote_removal(t_list **task_list);

/* wildcard_expansion.c */
bool		handle_wildcard_expansion(
				t_list **expanded_list, t_list **task_list);

/* wildcard_expansion_utils.c */
bool		is_wildcard(char *word, t_list *task_list);
char		*get_next_wildcard(char *word, t_list *task_list);
void		skip_wildcard(char **filename, char **word, t_list *task_list);

/* wildcard_file_list.c */
bool		set_file_list(t_list **file_list);
void		sort_file_list(t_list **file_list);

/* wildcard_task_list.c */
bool		set_wildcard_task_list(
				t_list **task_list, t_list *expanded_list, t_expd_op op_mask);

/* word_splitting.c */
bool		handle_word_splitting(
				t_list **expanded_list, t_expd_op op_mask, t_list **task_list);

/* word_splitting_utils.c */
char		*split_base_str(char **base_str, int *i, int *end);
int			trim_front_whitespace(char **base_str, int *i, int *end);
bool		append_rest_to_list(
				t_list **expanded_list,
				t_list *task_node,
				char *rest,
				int trimmed_len);

#endif
