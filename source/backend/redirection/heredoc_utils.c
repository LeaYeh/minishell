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


bool	expand_heredoc_content(t_shell *shell, t_list **line_list)
{
	t_list	*expanded_list;

	expanded_list = NULL;
	if (expand_list(shell, *line_list, &expanded_list) != SUCCESS)
		return (ft_lstclear(&expanded_list, free), false);
	ft_lstclear(line_list, free);
	*line_list = expanded_list;
	return (true);
}

bool	expand_heredoc_line(t_shell *shell, char **line)
{
	t_list	*expanded_list;

	expanded_list = NULL;
	if (ft_expander(
			*line, &expanded_list, shell, EXPAND | RM_QUOTES) != SUCCESS)
		return (ft_lstclear(&expanded_list, free), false);
	if (ft_lstsize_non_null(expanded_list) == 0)
		return (ft_lstclear(&expanded_list, free), true);
	replace_string_content(line, expanded_list->content);
	return (ft_lstclear(&expanded_list, free), true);
}

bool	remove_here_end_quote(
	t_shell *shell, t_io_red *io_red, bool *need_content_expansion)
{
	t_list	*expanded_list;

	expanded_list = NULL;
	if (is_here_end_quoted(io_red->here_end))
		*need_content_expansion = false;
	if (ft_expander(
			io_red->here_end, &expanded_list, shell, RM_QUOTES) != SUCCESS)
		return (ft_lstclear(&expanded_list, free), false);
	if (!replace_string_content(&io_red->here_end, expanded_list->content))
		return (ft_lstclear(&expanded_list, free), false);
	return (ft_lstclear(&expanded_list, free), true);
}

bool	append_line_to_list(char *line, t_list **line_list)
{
	char	*line_copy;

	line_copy = ft_strdup(line);
	if (!line_copy)
		return (false);
	if (!ft_lstnew_back(line_list, line_copy))
		return (free(line_copy), false);
	return (true);
}
