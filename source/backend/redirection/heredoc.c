/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:57:23 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/14 17:15:46 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "signals.h"

bool	setup_tmp_hdfile(int cmdtable_id, t_io_red *io_red)
{
	int	fd;

	io_red->in_file = generate_tmp_filename(cmdtable_id, "hd");
	if (!io_red->in_file)
		return (false);
	fd = open(io_red->in_file,
			O_CREAT | O_RDWR | O_TRUNC,
			(S_IRUSR + S_IWUSR) | S_IRGRP | S_IROTH);
	if (fd < 0 || close(fd) == -1)
	{
		perror(PROGRAM_NAME);
		return (ft_free_and_null((void **)&io_red->in_file), false);
	}
	return (true);
}

int	exec_heredoc(t_shell *shell, int cmdtable_id, t_io_red *io_red)
{
	char	*line;

	if (!setup_tmp_hdfile(cmdtable_id, io_red))
		return (HEREDOC_ERROR);
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (shell->exit_code == TERM_BY_SIGNAL + SIGINT)
			return (remove_file(io_red->in_file), free(line), HEREDOC_ABORT);
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, ERROR_HEREDOC_UNEXPECTED_EOF,
				PROGRAM_NAME, io_red->here_end);
			return (HEREDOC_SUCCESS);
		}
		if (ft_strcmp(line, io_red->here_end) == 0)
			break ;
		if (!append_line_to_file(line, io_red->in_file))
			return (remove_file(io_red->in_file), free(line), HEREDOC_ERROR);
		free(line);
	}
	free(line);
	return (HEREDOC_SUCCESS);
}

int	handle_heredoc(t_shell *shell, int cmdtable_id, t_list *io_red_list)
{
	t_io_red	*io_red;
	int			ret;

	while (io_red_list && io_red_list->content)
	{
		io_red = (t_io_red *)io_red_list->content;
		if (io_red->type == T_HERE_DOC)
		{
			shell->exit_code = SUCCESS;
			ret = exec_heredoc(shell, cmdtable_id, io_red);
			if (ret != HEREDOC_SUCCESS)
				return (ret);
		}
		io_red_list = io_red_list->next;
	}
	return (HEREDOC_SUCCESS);
}

// If the heredoc delimiter has quotes,
//     1. the here-document lines shall not undergo expansion
//     2. the delimiter will remove the quotes
int	ft_heredoc(t_shell *shell)
{
	t_cmd_table	*cur_cmd_table;
	t_list_d	*cmd_table_node;
	int			ret;

	cmd_table_node = shell->cmd_table_list;
	while (cmd_table_node && cmd_table_node->content)
	{
		cur_cmd_table = cmd_table_node->content;
		if (cur_cmd_table->type != C_SIMPLE_CMD)
		{
			cmd_table_node = cmd_table_node->next;
			continue ;
		}
		ret = handle_heredoc(
				shell, cur_cmd_table->id, cur_cmd_table->io_red_list);
		if (ret != HEREDOC_SUCCESS)
			return (ret);
		cmd_table_node = cmd_table_node->next;
	}
	return (HEREDOC_SUCCESS);
}
