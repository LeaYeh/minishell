/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:05:16 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/23 16:22:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"

void	ft_executor(t_shell *shell);

void	handle_process(t_shell *shell, t_list_d *cmd_table_node);
void	fork_subshell(t_shell *shell, t_list_d **cmd_table_node);
void	fork_pipeline(t_shell *shell, t_list_d **cmd_table_list);
void	fork_simple_cmd(t_shell *shell, t_list_d **cmd_table_list);
void	handle_control_op(t_shell *shell, t_list_d **cmd_table_node);
void	handle_assignment(t_shell *shell, t_final_cmd_table *final_cmd_table);
void	handle_external_cmd(t_shell *shell, t_cmd_table *cmd_table);
void	handle_builtin(t_shell *shell, t_list_d **cmd_table_node);
// void	handle_builtin(t_shell *shell,
// 			t_list_d **cmd_table_node, t_final_cmd_table *final_cmd_table);

/* Redirection */
bool	restore_std_io(int saved_std_io[2]);
bool	save_std_io(int saved_std_io[2]);
bool	redirect_scmd_io(t_shell *shell, int *read_fd, int *write_fd);
int 	redirect_subshell_io(t_shell *shell, t_cmd_table *cmd_table);
int 	handle_io_redirect(
            t_shell *shell, int *read_fd, int *write_fd, t_list *io_red_list);

/* Redirection - Pipe */
bool	need_pipe(t_list_d *cmd_table_node);
bool	create_pipe(t_pipe *new_pipe);
void	safe_close_pipe(t_pipe *pipe);
void	handle_pipes_parent(t_pipe *new_pipe, t_pipe *old_pipe);
void	handle_pipes_child(t_pipe *new_pipe, t_pipe *old_pipe);
void	safe_close_all_pipes(t_shell *shell);
// void	safe_move_nonempty_pipe(t_pipe *from, t_pipe *to);
void	replace_fd(int *from_end, int *to_end);

#endif
