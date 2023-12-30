/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:18:23 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/30 20:18:52 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

// TODO: file name length by define
// TODO: replace sprintf with ft_sprintf
char	*generate_tmp_filename(int cmdtable_id, char *category)
{
	char	*filename;

	filename = (char *)malloc(sizeof(char) * 256);
	if (!filename)
		return (NULL);
	sprintf(filename, "/tmp/%s_%s_%d-%d",
		PROGRAM_NAME, category, getpid(), cmdtable_id);
	return (filename);
}

void	remove_file(char **filename)
{
	unlink(*filename);
	ft_free_and_null((void **)filename);
}
