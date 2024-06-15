/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:37:38 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/04 23:26:17 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "defines.h"

t_hd_st	heredoc(t_sh *shell);
bool	setup_tmp_hdfile(int cmdtable_id, t_io_red *io_red);
t_hd_st	expand_heredoc_content(t_sh *shell, char **content);
bool	remove_here_end_quote(
			t_sh *shell, t_io_red *io_red, bool *need_content_expansion);
bool	append_line_to_list(t_list **line_list, char *line);
bool	is_str_quoted(char *str);
char	*concat_list_to_string(t_list *list, char *delim);

#endif
