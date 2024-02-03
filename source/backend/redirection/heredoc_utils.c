#include "defines.h"
#include "utils.h"
#include "expander.h"
#include "signals.h"

bool	is_here_end_quoted(char *here_end)
{
	if (ft_strchr(here_end, '\'') || ft_strchr(here_end, '\"'))
		return (true);
	return (false);
}

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

bool	expand_heredoc_content(t_shell *shell, t_list **line_list)
{
	t_list	*expanded_list;

	expanded_list = NULL;
	if (expand_list(shell, *line_list, &expanded_list, E_HEREDOC) != SUCCESS)
		return (ft_lstclear(&expanded_list, free), false);
	ft_lstclear(line_list, free);
	*line_list = expanded_list;
	return (true);
}

bool	remove_here_end_quote(
	t_shell *shell, t_io_red *io_red, bool *need_content_expansion)
{
	t_list	*expanded_list;

	expanded_list = NULL;
	if (is_here_end_quoted(io_red->here_end))
		*need_content_expansion = false;
	if (ft_expander(
			io_red->here_end, &expanded_list, shell, E_RM_QUOTES) != SUCCESS)
		return (ft_lstclear(&expanded_list, free), false);
	if (!replace_string_content(&io_red->here_end, expanded_list->content))
		return (ft_lstclear(&expanded_list, free), false);
	return (ft_lstclear(&expanded_list, free), true);
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
