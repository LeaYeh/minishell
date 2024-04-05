/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:09:31 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 17:47:36 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "executor.h"

bool	need_pipe(t_list_d *cmd_table_node)
{
	if (get_cmd_table_type_from_list(cmd_table_node) == C_SUBSHELL_START)
		move_past_subshell(&cmd_table_node);
	else if (get_cmd_table_type_from_list(cmd_table_node) == C_SIMPLE_CMD)
		cmd_table_node = cmd_table_node->next;
	if (get_cmd_table_type_from_list(cmd_table_node) == C_PIPE)
		return (true);
	return (false);
}

void	init_pipe(t_pipe *pipe)
{
	pipe->pipe_fd[0] = -1;
	pipe->pipe_fd[1] = -1;
	pipe->read_fd = &pipe->pipe_fd[0];
	pipe->write_fd = &pipe->pipe_fd[1];
}

bool	create_pipe(t_pipe *new_pipe)
{
	if (new_pipe->pipe_fd[0] != -1 || new_pipe->pipe_fd[1] != -1)
	{
		ft_dprintf(STDERR_FILENO, "Warning: Pipe is not empty\n");
		safe_close_pipe(new_pipe);
	}
	if (pipe(new_pipe->pipe_fd) == -1)
		return (false);
	return (true);
}
