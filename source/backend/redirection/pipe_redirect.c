/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:18:11 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/23 16:22:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "clean.h"

void	safe_close_pipe(t_pipe *pipe)
{
	safe_close(pipe->read_fd);
	safe_close(pipe->write_fd);
}

void	replace_fd(int *from_end, int *to_end)
{
	if (*from_end == -1)
		return ;
	safe_close(to_end);
	*to_end = *from_end;
	*from_end = -1;
}

void	handle_pipes_parent(t_pipe *new_pipe, t_pipe *old_pipe)
{
	safe_close(new_pipe->write_fd);
	replace_fd(new_pipe->read_fd, old_pipe->read_fd);
}

void	handle_pipes_child(t_pipe *new_pipe, t_pipe *old_pipe)
{
	safe_close(new_pipe->read_fd);
	replace_fd(new_pipe->write_fd, old_pipe->write_fd);
}

void	safe_close_all_pipes(t_shell *shell)
{
	safe_close_pipe(&shell->old_pipe);
	safe_close_pipe(&shell->new_pipe);
}

// void	safe_move_nonempty_pipe(t_pipe *from, t_pipe *to)
// {
// 	if (*to->read_fd != -1 || *to->write_fd != -1)
// 		printf("Warning: Pipe is not empty\n");
// 	if (*from->read_fd != -1 && *to->read_fd != -1)
// 	{
// 		*to->read_fd = *from->read_fd;
// 		*from->read_fd = -1;
// 	}
// 	if (*from->write_fd != -1 && *to->write_fd != -1)
// 	{
// 		*to->write_fd = *from->write_fd;
// 		*from->write_fd = -1;
// 	}
// }

bool	need_pipe(t_list_d *cmd_table_node)
{
	int	cmd_table_type;

	cmd_table_type = get_cmd_table_type_from_list(cmd_table_node);
	if (cmd_table_type == C_SUBSHELL_START)
		move_past_subshell(&cmd_table_node);
	else if (cmd_table_type == C_SIMPLE_CMD)
		cmd_table_node = cmd_table_node->next;
	if (get_cmd_table_type_from_list(cmd_table_node) == C_PIPE)
		return (true);
	return (false);
}

bool	create_pipe(t_pipe *new_pipe)
{
	if (new_pipe->pipe_fd[0] != -1 || new_pipe->pipe_fd[1] != -1)
	{
		printf("Warning: Pipe is not empty\n");
		safe_close_pipe(new_pipe);
	}
	if (pipe(new_pipe->pipe_fd) == -1)
		return (false);
	return (true);
}
