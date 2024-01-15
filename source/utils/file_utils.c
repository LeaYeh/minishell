/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:18:23 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/14 18:59:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

// TODO: file name length by define
// TODO: replace sprintf with ft_sprintf
char	*generate_tmp_filename(int cmdtable_id, char *category)
{
	char	*filename;

	filename = (char *)malloc(sizeof(char) * NAME_MAX);
	if (!filename)
		return (NULL);
	sprintf(filename, "/tmp/%s_%s_%d-%d",
		PROGRAM_NAME, category, getpid(), cmdtable_id);
	return (filename);
}

void	remove_file(char *filename)
{
	if (unlink(filename) == -1)
		ft_dprintf(2, ERROR_REMOVE_FILE, PROGRAM_NAME, filename);
}

bool	append_line_to_file(char *line, char *filename)
{
	int	fd;

	fd = open(filename,
			O_CREAT | O_RDWR | O_APPEND,
			(S_IRUSR + S_IWUSR) | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		perror(PROGRAM_NAME);
		return (false);
	}
	ft_putendl_fd(line, fd);
	return (close(fd) != -1);
}

void	safe_close(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}
