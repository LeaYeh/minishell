/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:37:33 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/26 02:30:04 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "utils.h"

bool	check_dir(char *dir, char *target_dir)
{
	if (is_dir(dir))
		return (true);
	ft_dprintf(2, "%s: cd: %s: ", PROGRAM_NAME, target_dir);
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

bool	is_abs_path(char *path)
{
	return (path && path[0] == '/');
}
