/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_file_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:57:11 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/31 23:47:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	set_file_list(t_list **file_list)
{
	DIR				*dir;
	struct dirent	*file;
	char			*filename;

	errno = SUCCESS;
	dir = opendir(".");
	if (dir == NULL)
		return (true);
	file = readdir(dir);
	while (file != NULL)
	{
		filename = ft_strdup(file->d_name);
		if (!filename || !ft_lstnew_front(file_list, filename))
		{
			free(filename);
			break ;
		}
		file = readdir(dir);
	}
	closedir(dir);
	return (errno == SUCCESS);
}

void	sort_file_list(t_list **file_list)
{
	ft_lstsort_merge(file_list, (void *)ft_alphabetic);
}
