/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_file_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:57:11 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/30 12:20:06 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	ascending(const char *str1, const char *str2)
{
	return (ft_strcmp(str1, str2) <= 0);
}

bool	alphabetic(const char *str1, const char *str2)
{
	// Skip non-alphanumeric characters
	while (!ft_isalnum(*str1) && *str1)
		str1++;
	while (!ft_isalnum(*str2) && *str2)
		str2++;

	// Compare digits
	if (ft_isdigit(*str1) && ft_isalpha(*str2))
		return (true);
	if (ft_isalpha(*str1) && ft_isdigit(*str2))
		return (false);
	if (ft_isdigit(*str1) && ft_isdigit(*str2))
		return (*str1 <= *str2);

	if (ft_isalpha(*str1) && ft_isalpha(*str2))
	{
		if (ft_tolower(*str1) == ft_tolower(*str2))
			return (*str1 >= *str2);
		else
			return (ft_tolower(*str1) <= ft_tolower(*str2));
	}
	return (*str1 <= *str2);
}

void	sort_file_list(t_list **file_list)
{
	ft_lstsort_merge(file_list, (void *)alphabetic);
}

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
		if (!filename)
			break ;
		if (!ft_lstnew_front(file_list, filename))
			break ;
		file = readdir(dir);
	}
	closedir(dir);
	return (errno == SUCCESS);
}
