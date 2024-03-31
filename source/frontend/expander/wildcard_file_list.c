/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_file_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:57:11 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/30 21:35:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	alphabetic(char *str1, char *str2)
{
	char	*str1_start;
	char	*str2_start;

	// Non-equal alnum
	str1_start = str1;
	str2_start = str2;
	while (*str1 && *str2)
	{
		if (ft_isalnum(*str1) && ft_isalnum(*str2))
		{
			if (ft_tolower(*str1) != ft_tolower(*str2))
				return (ft_tolower(*str1) <= ft_tolower(*str2));
			str1++;
			str2++;
		}
		while (!ft_isalnum(*str1) && *str1)
			str1++;
		while (!ft_isalnum(*str2) && *str2)
			str2++;
	}
	if (*str1 && !*str2)
		return (false);
	if (!*str1 && *str2)
		return (true);

	// Equal alnum
	str1 = str1_start;
	str2 = str2_start;
	while (*str1 && *str2)
	{
		if (ft_isalnum(*str1) && ft_isalnum(*str2))
		{
			if (ft_tolower(*str1) == ft_tolower(*str2) && *str1 != *str2)
				return (*str1 >= *str2);
			str1++;
			str2++;
		}
		while (!ft_isalnum(*str1) && *str1)
			str1++;
		while (!ft_isalnum(*str2) && *str2)
			str2++;
	}
	if (*str1 && !*str2)
		return (false);
	if (!*str1 && *str2)
		return (true);

	// Non-equal non-alnum
	str1 = str1_start;
	str2 = str2_start;
	while (*str1 && *str2)
	{
		if (!ft_isalnum(*str1) && ft_isalnum(*str2))
			return (true);
		if (ft_isalnum(*str1) && !ft_isalnum(*str2))
			return (false);
		if (!ft_isalnum(*str1) && !ft_isalnum(*str2) && *str1 != *str2)
			return (*str1 <= *str2);
		str1++;
		str2++;
	}
	if (*str1 && !*str2)
		return (false);
	if (!*str1 && *str2)
		return (true);

	str1 = str1_start;
	str2 = str2_start;
	return (ft_strcmp(str1, str2) <= 0);
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
