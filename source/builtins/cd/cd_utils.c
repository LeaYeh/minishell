/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:37:33 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/20 20:32:26 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

#include "expander.h"	// Move replace_part_of_str() to utils or libft

bool	is_absolute_path(char *path)
{
	return (path[0] == '/');
}

// TODO:
// [ ] Just use the relative path, including dot components, with stat().
// [ ] Store the absolute path in every node.
// [ ] function that converts a list to a path, up to a specified node.
// // [ ] function that gets the position of a node in a linked list.
bool	check_directory(char *cleaned_path, char *og_path)
{
	struct stat	path_stat;

	if (access(cleaned_path, F_OK) != -1)
	{
		stat(cleaned_path, &path_stat);
		if (S_ISDIR(path_stat.st_mode))
			return (true);
		ft_dprintf(2, "%s: cd: %s: Not a directory\n", \
		PROGRAM_NAME, og_path);	//TODO: Try to replace with perror()
	}
	else
		ft_dprintf(2, "%s: cd: %s: No such file or directory\n", \
		PROGRAM_NAME, og_path);	//TODO: Try to replace with perror()
	return (false);
}

bool	convert_relative_to_absolute_path(char **curpath, char *pwd)
{
	int		end;
	char	*result;

	result = ft_strdup(pwd);
	if (!result)
		return (false);
	end = ft_strlen(result);
	if (result[end - 1] != '/')
	{
		if (!replace_part_of_str(&result, "/", end, 1))
			return (free(result), false);
		end++;
	}
	if (!replace_part_of_str(&result, *curpath, end, 1))
		return (free(result), false);
	free(*curpath);
	*curpath = result;
	return (true);
}

//TODO: Doesn't necessarily need an absolute path, so maybe adjust the function name
char	*try_to_convert_absolute_to_relative_path(char *abs_path, char *pwd)
{
	size_t	abs_path_len;
	size_t	pwd_len;
	char	*rel_path;

	abs_path_len = ft_strlen(abs_path);
	// Can pwd be NULL?
	pwd_len = ft_strlen(pwd);
	if (abs_path_len < pwd_len || \
		ft_strncmp(abs_path, pwd, pwd_len) != 0 || \
		(abs_path[pwd_len] != '/' && abs_path[pwd_len] != '\0'))
		return (abs_path);
	rel_path = ft_substr(abs_path, pwd_len + 1, abs_path_len - pwd_len);
	return (free(abs_path), rel_path);
}
