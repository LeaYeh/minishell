/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:05:16 by lyeh              #+#    #+#             */
/*   Updated: 2024/06/07 07:25:53 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"

void	executor(t_sh *shell);
int		set_expanded_cmd_name(
			char **cmd_name, t_sh *shell, t_list *simple_cmd_list);
void	handle_expansion_error(t_sh *shell, t_list_d **cmd_table_node, int ret);

void	handle_process(t_sh *shell, t_list_d *cmd_table_node);
void	fork_subshell(t_sh *shell, t_list_d **cmd_table_node);
void	fork_pipeline(t_sh *shell, t_list_d **cmd_table_list);
void	fork_simple_cmd(t_sh *shell, t_list_d **cmd_table_list);
void	handle_control_op(t_sh *shell, t_list_d **cmd_table_node);
void	handle_external_cmd(t_sh *shell, t_ct *cmd_table);
void	handle_builtin(t_sh *shell, t_list_d **cmd_table_node);
bool	wait_process(t_sh *shell, pid_t pid);
void	wait_all_child_pid(t_sh *shell);

/* Redirection */
void	safe_close(int *fd);
void	replace_fd(int *from_end, int *to_end);
bool	restore_std_io(int saved_std_io[2]);
bool	save_std_io(int saved_std_io[2]);
bool	redirect_scmd_io(t_sh *shell, int *read_fd, int *write_fd);
int		redirect_subshell_io(t_sh *shell, t_ct *cmd_table);
int		open_io_files(
			t_sh *shell, int *read_fd, int *write_fd, t_list *io_red_list);

/* Redirection - Pipe */
bool	need_pipe(t_list_d *cmd_table_node);
bool	create_pipe(t_pipe *new_pipe);
void	init_pipe(t_pipe *pipe);
void	safe_close_pipe(t_pipe *pipe);
void	handle_pipes_parent(t_pipe *new_pipe, t_pipe *old_pipe);
void	handle_pipes_child(t_pipe *new_pipe, t_pipe *old_pipe);
void	safe_close_all_pipes(t_sh *shell);

#endif
