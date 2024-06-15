/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:02:03 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/04 22:59:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "defines.h"

void	print_env_list(t_sh *shell);
void	print_env(t_env *env);
void	print_token_list(t_list *token_list);
void	print_token(t_tok *token);
void	print_state_stack(t_list *stack);
void	print_parse_stack(t_list *node);
bool	print_ast_bfs(t_ast *root);
void	print_cmd_table_list(t_list_d *cmd_table_list);
void	print_cmd_table(t_ct *cmd_table);
void	print_simple_cmd_list(t_list *simple_cmd_list);
void	print_assignment_list(t_list *assignment_list);
void	print_io_red_list(t_list *io_red_list);
void	print_final_cmd_table(t_fct *final_cmd_table);

/* Expanded cmd table */
bool	print_expanded_cmd_table_list(t_sh *shell);
void	print_operator_cmd_table(t_ct *cmd_table);
bool	print_expanded_cmd_table(t_ct *cmd_table, t_sh *shell);
void	print_unexpanded_cmd_table(t_ct *cmd_table);
bool	print_expanded_simple_cmd_list(t_ct *cmd_table, t_sh *shell);
bool	print_expanded_assignment_list(t_ct *cmd_table, t_sh *shell);
bool	print_expanded_io_red_list(t_ct *cmd_table, t_sh *shell);
bool	print_expanded_str(char *str, t_sh *shell, t_expd_op op_mask);

/* Expander task list */
bool	print_expander_task_list(t_list *task_list, char *calling_function);
bool	print_expander_task_node(t_list *task_node);
char	*get_expander_task_type_name(t_expd_tsk_typ type);

#endif
