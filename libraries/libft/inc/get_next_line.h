/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:28:58 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/27 09:09:28 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	128
# endif
# define FD_MAX			1048576
# define NO_NL			-1

typedef struct s_buf
{
	char			buf[BUFFER_SIZE + 1];
	ssize_t			bytes_unsaved;
	ssize_t			line_end;
	char			endoffile;
	struct s_buf	*next;
}	t_buf;

\
/* get_next_line.c */
char	*get_next_line(int fd);
int		check_for_full_leftover_line(t_buf **head, char **result);
int		read_until_endofline(t_buf **head, int fd);
char	*copy_into_result_and_move_head_to_tail(t_buf **head);

\
/* get_next_line_utils.c */
int		add_new_node(t_buf *cur);
size_t	count_result_size(t_buf *cur);
ssize_t	find_endofline(t_buf *cur);
void	free_list(t_buf **head);
int		initial_check(int fd, t_buf **head);

\
/* free_get_next_line.c */
void	free_get_next_line(void);

#endif
