/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:37:33 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/21 17:40:50 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "utils.h"

bool	check_dir(char *dir, char *target_dir)
{
	if (is_dir(dir))
		return (true);
	ft_dprintf(STDERR_FILENO, "%s: cd: %s: ", PROGRAM_NAME, target_dir);
	perror(NULL);
	return (false);
}

bool	ensure_path_not_empty(char **final_path)
{
	if (**final_path != '\0')
		return (true);
	free(*final_path);
	*final_path = ft_strdup(".");
	if (!*final_path)
		return (false);
	return (true);
}

char	*get_target_dir(char *args[], t_list *env_list)
{
	char	*target_dir;

	if (get_array_len(args) > 2)
		return (ft_dprintf(STDERR_FILENO,
				ERROR_CD_TOO_MANY_ARGS, PROGRAM_NAME), NULL);
	if (!args[1])
	{
		target_dir = get_value_from_env_list(env_list, "HOME");
		if (!target_dir)
			return (ft_dprintf(STDERR_FILENO,
					ERROR_CD_HOME_NOT_SET, PROGRAM_NAME), NULL);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target_dir = get_value_from_env_list(env_list, "OLDPWD");
		if (!target_dir)
			return (ft_dprintf(STDERR_FILENO,
					ERROR_CD_OLDPWD_NOT_SET, PROGRAM_NAME), NULL);
	}
	else
		target_dir = args[1];
	return (target_dir);
}

bool	is_abs_path(char *path)
{
	return (path && path[0] == '/');
}
