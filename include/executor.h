/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:05:16 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/11 21:14:13 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"

void	ft_executor(t_shell *shell);

bool	ft_heredoc(t_list_d *cmd_table_list);

void	handle_process(t_shell *shell, t_list_d *cmd_table_node);
void	handle_subshell(t_shell *shell, t_list_d **cmd_table_node);
void	handle_control_op(t_shell *shell, t_list_d **cmd_table_node);
void	handle_pipeline(t_shell *shell, t_list_d **cmd_table_list);
void	handle_simple_cmd(t_shell *shell, t_list_d **cmd_table_list);
void	handle_assignment(t_shell *shell, t_final_cmd_table *final_cmd_table);
void	handle_external_cmd(t_shell *shell, t_final_cmd_table *final_cmd_table);
void	handle_builtin(t_shell *shell,
			t_list_d **cmd_table_node, t_final_cmd_table *final_cmd_table);

/* Error checker */
bool	check_executable(char *filename);
bool	check_file(char *filename, int o_flag, int permission);

/* Utils */
char	*get_exec_path(char *cmd_name, char **envp);

/* Expand cmd info utils */
int		set_expanded_cmd_info(t_shell *shell,
			t_final_cmd_table *final_cmd_table, char ***expanded_array);

/* Final cmd table utils */
bool	expand_final_cmd_table(
			t_shell *shell, t_final_cmd_table *final_cmd_table);

/* Redirection - Pipe */
bool	setup_subshell_pipe(t_list_d *cmd_table_node);
bool	setup_normal_pipe(t_list_d *cmd_table_node);

#endif
