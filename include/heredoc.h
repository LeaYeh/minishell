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
bool	append_line_to_list(char *line, t_list **line_list);

#endif
