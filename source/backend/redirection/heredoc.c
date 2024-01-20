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

bool	setup_tmp_hdfile(int cmdtable_id, t_io_red **io_red)
{
	int	fd;

	(*io_red)->out_file = generate_tmp_filename(cmdtable_id, "hd");
	if (!(*io_red)->out_file)
		return (false);
	fd = open((*io_red)->out_file,
			O_CREAT | O_RDWR | O_TRUNC,
			(S_IRUSR + S_IWUSR) | S_IRGRP | S_IROTH);
	if (fd < 0 || close(fd) == -1)
	{
		perror(PROGRAM_NAME);
		return (ft_free_and_null((void **)&(*io_red)->out_file), false);
	}
	return (true);
}

bool	exec_heredoc(int cmdtable_id, t_io_red **io_red)
{
	char	*line;

	if (!setup_tmp_hdfile(cmdtable_id, io_red))
		return (false);
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, ERROR_HEREDOC_UNEXPECTED_EOF,
				PROGRAM_NAME, (*io_red)->here_end);
			return (remove_file((*io_red)->out_file), true);
		}
		if (ft_strcmp(line, (*io_red)->here_end) == 0)
			break ;
		if (!append_line_to_file(line, (*io_red)->out_file))
			return (remove_file((*io_red)->out_file), free(line), false);
		free(line);
	}
	free(line);
	return (true);
}

bool	handle_heredoc(int cmdtable_id, t_list *io_red_list)
{
	while (io_red_list && io_red_list->content)
	{
		if (((t_io_red *)io_red_list->content)->type == T_HERE_DOC)
		{
			if (!exec_heredoc(cmdtable_id, (t_io_red **)&io_red_list->content))
				return (false);
		}
		io_red_list = io_red_list->next;
	}
	return (true);
}

// If the heredoc delimiter has quotes,
//     1. the here-document lines shall not undergo expansion
//     2. the delimiter will remove the quotes
bool	ft_heredoc(t_list_d *cmd_table_list)
{
	t_cmd_table	*cur_cmd_table;

	while (cmd_table_list && cmd_table_list->content)
	{
		cur_cmd_table = cmd_table_list->content;
		if (cur_cmd_table->type == C_SIMPLE_CMD)
			if (!handle_heredoc(cur_cmd_table->id, cur_cmd_table->io_red_list))
				return (false);
		cmd_table_list = cmd_table_list->next;
	}
	return (true);
}
