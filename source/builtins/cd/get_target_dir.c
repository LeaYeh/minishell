/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_target_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 02:32:28 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/26 02:32:41 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "utils.h"

# define ERROR_CD_OLDPWD_NOT_SET "cd: OLDPWD not set\n"

char	*get_target_dir(char **args, t_list *env_list)
{
	char	*target_dir;

	if (get_array_len(args) > 2)
	{
		ft_dprintf(2, ERROR_CD_TOO_MANY_ARGS, PROGRAM_NAME);
		return (NULL);
	}
	if (!args[1])
	{
		target_dir = get_value_from_env(env_list, "HOME");
		if (!target_dir)
			return (ft_dprintf(2, ERROR_CD_HOME_NOT_SET, PROGRAM_NAME), NULL);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target_dir = get_value_from_env(env_list, "OLDPWD");
		if (!target_dir)
			return (ft_dprintf(2, ERROR_CD_OLDPWD_NOT_SET, PROGRAM_NAME), NULL);
	}
	else
		target_dir = args[1];
	return (target_dir);
}
