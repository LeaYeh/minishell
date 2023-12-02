/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:06:25 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 20:17:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buf	*head[FD_MAX];
	char			*result;

	if (!initial_check(fd, &head[fd]))
		return (NULL);
	if (head[fd]->bytes_unsaved)
	{
		if (check_for_full_leftover_line(&head[fd], &result))
			return (result);
		if (!add_new_node(head[fd]))
			return (free_list(&head[fd]), NULL);
	}
	if (!read_until_endofline(&head[fd], fd))
		return (NULL);
	result = copy_into_result_and_move_head_to_tail(&head[fd]);
	if (!result)
		return (NULL);
	head[fd]->bytes_unsaved -= head[fd]->line_end + 1;
	if (head[fd]->bytes_unsaved == 0)
		free_list(&head[fd]);
	return (result);
}

int	check_for_full_leftover_line(t_buf **head, char **result)
{
	ssize_t	i;
	ssize_t	new_line_end;
	ssize_t	result_size;

	new_line_end = find_endofline(*head);
	if (new_line_end != NO_NL)
	{
		result_size = new_line_end - (*head)->line_end;
		*result = (char *) malloc(result_size + 1);
		if (!*result)
			return (free_list(head), 1);
		i = 0;
		(*head)->line_end++;
		while (i < result_size)
			(*result)[i++] = (*head)->buf[(*head)->line_end++];
		(*result)[i] = '\0';
		(*head)->bytes_unsaved -= result_size;
		if ((*head)->bytes_unsaved)
			(*head)->line_end = new_line_end;
		else
			free_list(head);
		return (1);
	}
	return (0);
}

int	read_until_endofline(t_buf **head, int fd)
{
	t_buf	*cur;

	if ((*head)->next)
		cur = (*head)->next;
	else
		cur = *head;
	while (cur)
	{
		cur->bytes_unsaved = read(fd, cur->buf, BUFFER_SIZE);
		if (cur->bytes_unsaved == -1 || (*head)->bytes_unsaved == 0)
			return (free_list(head), 0);
		if (BUFFER_SIZE <= SSIZE_MAX && cur->bytes_unsaved != BUFFER_SIZE)
			cur->endoffile = 1;
		cur->buf[cur->bytes_unsaved] = '\0';
		cur->line_end = find_endofline(cur);
		if (cur->line_end == NO_NL && !cur->endoffile)
			if (!add_new_node(cur))
				return (free_list(head), 0);
		cur = cur->next;
	}
	return (1);
}

char	*copy_into_result_and_move_head_to_tail(t_buf **head)
{
	t_buf	*cur;
	char	*result;
	size_t	i;
	ssize_t	j;

	result = (char *) malloc(count_result_size(*head) + 1);
	if (!result)
		return (free_list(head), NULL);
	i = 0;
	while ((*head)->next)
	{
		cur = *head;
		(*head) = (*head)->next;
		j = cur->line_end + 1;
		while (cur->buf[j])
			result[i++] = cur->buf[j++];
		free(cur);
	}
	j = 0;
	while (j <= (*head)->line_end)
		result[i++] = (*head)->buf[j++];
	result[i] = '\0';
	return (result);
}
