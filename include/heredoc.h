/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:37:38 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 18:37:39 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "defines.h"
# include "utils.h"
# include "expander.h"
# include "signals.h"

int		ft_heredoc(t_shell *shell);
bool	is_here_end_quoted(char *here_end);
bool	setup_tmp_hdfile(int cmdtable_id, t_io_red *io_red);
int		expand_heredoc_content(t_shell *shell, char **content);
bool	remove_here_end_quote(t_shell *shell,
			t_io_red *io_red, bool *need_content_expansion);
bool	append_line_to_list(t_list **line_list, char *line);

#endif
