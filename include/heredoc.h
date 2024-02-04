#ifndef HEREDOC_H
# define HEREDOC_H

# include "defines.h"
# include "utils.h"
# include "expander.h"
# include "signals.h"

int		ft_heredoc(t_shell *shell);
bool	setup_tmp_hdfile(int cmdtable_id, t_io_red *io_red);
bool	expand_heredoc_content(t_shell *shell, t_list **line_list);
bool	remove_here_end_quote(t_shell *shell,
			t_io_red *io_red, bool *need_content_expansion);
bool	write_content_to_file(char *content, char *filename);
bool	append_line_to_list(t_list **line_list, char *line);

#endif
