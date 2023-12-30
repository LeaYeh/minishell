/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:57:23 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/30 20:18:48 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

bool	setup_tmp_hdfile(int cmdtable_id, t_io_red **io_red)
{
	int	fd;

	(*io_red)->out_file = generate_tmp_filename(cmdtable_id);
	if (!(*io_red)->out_file)
		return (false);
	fd = open((*io_red)->out_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(PROGRAM_NAME);
		return (ft_free_and_null((void **)&(*io_red)->out_file), false);
	}
	(*io_red)->red_out = fd;
	close(fd);
	return (true);
}

bool	exec_heredoc(int cmdtable_id, t_io_red **io_red)
{
	char		*line;

	if (!setup_tmp_hdfile(cmdtable_id, io_red))
		return (false);
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
		{
			ft_dprintf(2, ERROR_HEREDOC_UNEXPECTED_EOF,
				PROGRAM_NAME, (*io_red)->here_end);
			remove_file(&(*io_red)->out_file);
			break ;
		}
		if (ft_strcmp(line, (*io_red)->here_end) == 0)
			break ;
		ft_putendl_fd(line, (*io_red)->red_out);
		ft_free_and_null((void **)&line);
	}
	ft_free_and_null((void **)&line);
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
