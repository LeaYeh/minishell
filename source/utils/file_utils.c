/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:18:23 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/19 16:12:01 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

char	*generate_tmp_filename(int cmdtable_id, char *category)
{
	char	*filename;

	filename = (char *)malloc(sizeof(char) * NAME_MAX);
	if (!filename)
		return (NULL);
	ft_snprintf(
		filename,
		NAME_MAX,
		"/tmp/%s_%s_%d-%d", PROGRAM_NAME, category, getpid(), cmdtable_id);
	return (filename);
}

void	remove_file(char *filename)
{
	if (unlink(filename) == -1)
		ft_dprintf(STDERR_FILENO, ERROR_REMOVE_FILE, PROGRAM_NAME, filename);
}

bool	write_content_to_file(char *content, char *filename)
{
	int	fd;

	fd = open(filename,
			O_CREAT | O_RDWR | O_TRUNC,
			(S_IRUSR + S_IWUSR) | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		perror(PROGRAM_NAME);
		return (false);
	}
	if (content)
		ft_dprintf(fd, "%s", content);
	return (close(fd) != -1);
}

void	safe_close(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

bool	is_dir(char *dir)
{
	struct stat	path_stat;

	if (access(dir, F_OK) != -1)
	{
		stat(dir, &path_stat);
		if (S_ISDIR(path_stat.st_mode))
			return (true);
	}
	return (false);
}
