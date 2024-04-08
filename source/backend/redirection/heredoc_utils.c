/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:08:56 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/19 15:08:57 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "expander.h"
#include "signals.h"

bool	setup_tmp_hdfile(int cmdtable_id, t_io_red *io_red)
{
	int	fd;

	io_red->filename = generate_tmp_filename(cmdtable_id, "hd");
	if (!io_red->filename)
		return (false);
	fd = open(io_red->filename,
			O_CREAT | O_RDWR | O_TRUNC,
			(S_IRUSR + S_IWUSR) | S_IRGRP | S_IROTH);
	if (fd < 0 || close(fd) == -1)
	{
		perror(PROGRAM_NAME);
		return (ft_free_and_null((void **)&io_red->filename), false);
	}
	return (true);
}

t_hd_st	expand_heredoc_content(t_sh *shell, char **content)
{
	t_list	*expanded_list;
	int		ret;

	expanded_list = NULL;
	ret = expander(*content, &expanded_list, shell, E_PARAM);
	if (ret == MALLOC_ERROR)
		return (ft_lstclear(&expanded_list, free), HD_ERROR);
	if (ret == BAD_SUBSTITUTION)
	{
		shell->exit_code = BAD_SUBSTITUTION;
		return (ft_lstclear(&expanded_list, free), HD_ABORT);
	}
	ft_free_and_null((void **)content);
	if (expanded_list)
		*content = expanded_list->content;
	ft_lstclear(&expanded_list, NULL);
	return (HD_SUCCESS);
}

bool	remove_here_end_quote(
			t_sh *shell, t_io_red *io_red, bool *need_content_expansion)
{
	t_list	*expanded_list;

	expanded_list = NULL;
	*need_content_expansion = false;
	if (expander(
			io_red->here_end, &expanded_list, shell, E_RM_QUOTES) != SUCCESS)
		return (ft_lstclear(&expanded_list, free), false);
	free(io_red->here_end);
	io_red->here_end = expanded_list->content;
	ft_lstclear(&expanded_list, NULL);
	return (true);
}

bool	append_line_to_list(t_list **line_list, char *line)
{
	char	*line_copy;

	line_copy = ft_strdup(line);
	if (!line_copy)
		return (false);
	if (!ft_lstnew_back(line_list, line_copy))
		return (free(line_copy), false);
	return (true);
}
