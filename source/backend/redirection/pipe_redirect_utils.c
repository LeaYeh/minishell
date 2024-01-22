#include "defines.h"
#include "utils.h"

void	init_pipe(t_pipe *pipe)
{
	pipe->pipe_fd[0] = -1;
	pipe->pipe_fd[1] = -1;
	pipe->read_fd = &pipe->pipe_fd[0];
	pipe->write_fd = &pipe->pipe_fd[1];
}

void	reset_pipe_fd(t_pipe *pipe)
{
	safe_close(pipe->read_fd);
	safe_close(pipe->write_fd);
	pipe->pipe_fd[0] = -1;
	pipe->pipe_fd[1] = -1;
}
