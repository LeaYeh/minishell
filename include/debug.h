/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:02:03 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/31 13:02:58 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "defines.h"

void	print_env_list(t_shell *shell);
void	print_token_list(t_list *token_list);
bool	print_ast_bfs(t_ast *root);
void	print_cmd_table_list(t_list_d *cmd_table_list);
void	print_cmd_table(t_cmd_table *cmd_table);
void	print_final_cmd_table(t_final_cmd_table *final_cmd_table);

/* Expanded cmd table */
bool	print_expanded_cmd_table_list(t_shell *shell);
void	print_operator_cmd_table(t_cmd_table *cmd_table);
bool	print_expanded_cmd_table(t_cmd_table *cmd_table, t_shell *shell);
void	print_unexpanded_cmd_table(t_cmd_table *cmd_table);
bool	print_expanded_simple_cmd_list(t_cmd_table *cmd_table, t_shell *shell);
bool	print_expanded_assignment_list(t_cmd_table *cmd_table, t_shell *shell);
bool	print_expanded_io_red_list(t_cmd_table *cmd_table, t_shell *shell);

/* Expander task list */
bool	print_expander_task_list(t_list *task_list, char *calling_function);
bool	print_expander_task_node(t_list *task_node);
char	*get_expander_task_type_name(t_expander_task_type type);

#endif
