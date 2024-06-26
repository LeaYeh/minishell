/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:18:23 by lyeh              #+#    #+#             */
/*   Updated: 2024/05/21 16:43:23 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*generate_tmp_filename(int cmdtable_id, char *category)
{
	char	*filename;

	filename = (char *)malloc(NAME_MAX * sizeof(char));
	if (!filename)
		return (NULL);
	ft_snprintf(
		filename,
		NAME_MAX,
		"/tmp/%s_%s_%d-%d",
		PROGRAM_NAME, category, getpid_from_proc(), cmdtable_id);
	return (filename);
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

void	remove_file(char *filename)
{
	struct stat	path_stat;

	if (stat(filename, &path_stat) == -1)
		return ;
	if (unlink(filename) == -1)
		print_error(ERROR_REMOVE_FILE, PROGRAM_NAME, filename);
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
