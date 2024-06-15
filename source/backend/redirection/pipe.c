/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:18:11 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/04 22:30:45 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

void	safe_close_pipe(t_pipe *pipe)
{
	safe_close(pipe->read_fd);
	safe_close(pipe->write_fd);
}

void	safe_close_all_pipes(t_sh *shell)
{
	safe_close_pipe(&shell->old_pipe);
	safe_close_pipe(&shell->new_pipe);
}
