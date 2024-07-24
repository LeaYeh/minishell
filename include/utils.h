/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:38:17 by lyeh              #+#    #+#             */
/*   Updated: 2024/05/03 17:16:26 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "defines.h"

/* User input utils */
bool		read_input(
				char **line,
				t_sh *shell,
				char *prompt,
				bool add_to_history);

/* Token list utils */
t_tok		*init_token(t_tok_typ type, char *data);
void		free_token(t_tok *token);
t_tok		*get_token_from_list(t_list *token_list);
t_tok_typ	get_token_type_from_list(t_list *token_list);
char		*get_token_data_from_list(t_list *token_list);
t_list		*dup_token_list(t_list *token_list);

/* AST utils */
t_ast		*init_ast_node(t_prs_elem element, char *data, t_list *children);
void		free_ast_node(t_ast *ast);

/* Redirect utils */
t_io_red	*init_io_red(void);
void		free_io_red(t_io_red *io_red);

/* Cmd table utils */
t_ct		*init_cmd_table(void);
void		free_cmd_table(t_ct *cmd_table);
bool		append_cmd_table_by_scenario(
				t_tok_typ token_type, t_list_d **cmd_table_list);
t_ct		*get_cmd_table_from_list(t_list_d *cmd_table_node);
t_ct		*get_last_simple_cmd_table(t_list_d *cmd_table_list);
t_ct		*get_subshell_start(t_list_d *cmd_table_node);
bool		is_control_op_cmd_table(t_ct_typ cmd_table_type);
bool		is_scmd_in_pipeline(t_list_d *cmd_table_node);
t_ct_typ	get_cmd_table_type_from_list(t_list_d *cmd_table_list);
bool		is_builtin(char *cmd_name, t_sh *shell);
void		move_past_pipeline(t_list_d **cmd_table_node);
void		move_past_subshell(t_list_d **cmd_table_node);

/* Final cmd table utils */
int			set_final_cmd_table(t_sh *shell, t_ct *cmd_table);
void		free_final_cmd_table(t_fct **final_cmd_table);
bool		setup_exec_path(t_sh *shell, t_fct *final_cmd_table);
int			setup_simple_cmd(t_sh *shell, t_list *simple_cmd_list);
bool		setup_env(t_fct *final_cmd_table, t_list *env_list);
bool		set_exec_path(char **exec_path, char *cmd_name, char *env[]);
bool		setup_assignment_array(
				t_fct *final_cmd_table, t_list *assignment_list);
void		setup_fd(t_sh *shell, t_fct *final_cmd_table);

/* Environment utils */
bool		extract_env_key(char **res, const char *str);
bool		extract_env_value(char **res, const char *str);
char		*get_value_from_env(char *env[], char *key);
bool		is_key_in_env(char *env[], char *key);

bool		append_env_node(
				t_list **env_list, char **key, char **value, t_expt export);
void		free_env_node(t_env *env);
bool		is_key_in_env_list(t_list *env_list, char *key);
char		*get_value_from_env_list(t_list *env_list, char *key);
t_env		*find_env_node(t_list *env_list, char *key, char *value);
bool		is_exported_env_node(t_list *env_list, char *key);
int			get_exported_env_size(t_list *env_list);
bool		process_str_to_env_list(
				char *str, t_list **env_list, t_expt export);
void		remove_env_node(t_list **env_list, char *key, char *value);
bool		replace_env_value(
				t_list *env_list, char *key, char **value, char **old_value);

/* Expansion utils */
int			expand_list(
				t_sh *shell,
				t_list *list,
				t_list **expanded_list,
				t_expd_op op_mask);

/* Array utils */
void		free_array(char **array[]);
int			get_array_len(char *arr[]);
char		**convert_list_to_string_array(t_list *list);
char		**append_string_array(char *array[], char *str);

/* Type utils */
bool		is_word(t_tok_typ token_type);
bool		is_io_red_op(t_tok_typ token_type);
bool		is_control_op(t_tok_typ token_type);
bool		is_subshell_symbol(t_tok_typ token_type);

/* File utils */
char		*generate_tmp_filename(int cmdtable_id, char *category);
bool		write_content_to_file(char *content, char *filename);
void		remove_file(char *filename);
bool		is_dir(char *dir);

/* Stack utils */
int			get_state_from_stack(t_list *node);
t_tok		*get_token_from_stack(t_list *node);
t_ast		*get_ast_from_stack(t_list *node);
bool		drop_num_stack(t_list **stack, int num, void (*del)(void *));
t_list		*pop_num_stack(t_list **stack, int num);

/* Symbol utils */
bool		skip_single_quote(char *str, int *i);
bool		skip_double_quote(char *str, int *i);
bool		skip_dollar_brace(char *str, int *i, bool is_in_dquote);
bool		is_open_pair(unsigned char c, t_pair_op operation);

/* Variable name utils */
bool		is_valid_varname(char *str);
bool		is_valid_varname_char(char c);
bool		is_valid_varname_start(char c);
char		*get_varname(char *str);

/* Print utils */
void		print_welcome_msg(t_sh *shell);
void		clear_terminal_soft(void);

/* Pid utils */
pid_t		getpid_from_proc(void);

/* Error utils */
void		print_error(char *fmt, ...);

#endif
