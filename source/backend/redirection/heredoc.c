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

#include "heredoc.h"

bool	handle_heredoc_content(t_shell *shell,
		char *filename, t_list **line_list, bool need_content_expansion)
{
	t_list	*line_node;
	char	*line;

	if (need_content_expansion)
	{
		if (!expand_heredoc_content(shell, line_list))
			return (ft_lstclear(line_list, free),
				remove_file(filename), HEREDOC_ERROR);
	}
	line_node = *line_list;
	while (line_node)
	{
		line = (char *)line_node->content;
		if (!append_line_to_file(line, filename))
			return (ft_lstclear(line_list, free),
				remove_file(filename), HEREDOC_ERROR);
		line_node = line_node->next;
	}
	return (ft_lstclear(line_list, free), HEREDOC_SUCCESS);
}

int	exec_heredoc(t_shell *shell,
		int cmdtable_id, t_io_red *io_red, bool need_content_expansion)
{
	t_list	*line_list;
	char	*line;

	if (!setup_tmp_hdfile(cmdtable_id, io_red))
		return (HEREDOC_ERROR);
	line_list = NULL;
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (shell->exit_code == TERM_BY_SIGNAL + SIGINT)
			return (free(line), ft_lstclear(&line_list, free),
				remove_file(io_red->in_file), HEREDOC_ABORT);
		if (!line)
			return (ft_dprintf(STDERR_FILENO, ERROR_HEREDOC_UNEXPECTED_EOF,
					PROGRAM_NAME, io_red->here_end), HEREDOC_SUCCESS);
		if (ft_strcmp(line, io_red->here_end) == 0)
			break ;
		if (!append_line_to_list(line, &line_list))
			return (free(line), ft_lstclear(&line_list, free),
				remove_file(io_red->in_file), HEREDOC_ERROR);
		free(line);
	}
	free(line);
	return (handle_heredoc_content(
			shell, io_red->in_file, &line_list, need_content_expansion));
}

int	handle_heredoc(t_shell *shell, int cmdtable_id, t_list *io_red_list)
{
	t_io_red	*io_red;
	int			ret;
	bool		need_content_expansion;

	while (io_red_list && io_red_list->content)
	{
		need_content_expansion = true;
		io_red = (t_io_red *)io_red_list->content;
		if (io_red->type == T_HERE_DOC)
		{
			if (!remove_here_end_quote(shell, io_red, &need_content_expansion))
				return (HEREDOC_ERROR);
			shell->exit_code = SUCCESS;
			ret = exec_heredoc(
					shell, cmdtable_id, io_red, need_content_expansion);
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
