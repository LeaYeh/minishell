/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:05:16 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/06 20:48:30 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"

void	ft_executor(t_shell *shell);

bool	ft_heredoc(t_list_d *cmd_table_list);

void	move_past_subshell(t_list_d **cmd_table_node);
void	handle_process(t_shell *shell, t_list_d **cmd_table_node);
void	handle_subshell(t_shell *shell, t_list_d **cmd_table_node);
void	handle_pipeline(t_shell *shell, t_list_d **cmd_table_list);
void	handle_simple_cmd(t_shell *shell, t_list_d *cmd_table_list);

/* Redirection - Pipe */
bool	setup_subshell_pipe(t_list_d *cmd_table_node);
bool	setup_normal_pipe(t_list_d *cmd_table_node);

#endif
