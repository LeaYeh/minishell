/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:18:11 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/19 15:11:56 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
