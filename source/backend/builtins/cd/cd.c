/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:05:20 by codespace         #+#    #+#             */
/*   Updated: 2024/03/18 17:41:31 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "clean.h"
#include "utils.h"

int	exec_cd(char *args[], t_list **env_list)
{
	char	*final_path;
	char	*new_pwd;
	int		ret;
	char	*target_dir;

	target_dir = get_target_dir(args, *env_list);
	if (!target_dir)
		return (GENERAL_ERROR);
	ret = set_final_path(&final_path, &new_pwd, target_dir);
	if (ret != SUCCESS)
		return (ret);
	if (chdir(final_path) == -1)
		return (free(final_path), free(new_pwd),
			handle_cd_error(errno, target_dir));
	free(final_path);
	if (!update_pwd_env(env_list, new_pwd))
		return (free(new_pwd), BUILTIN_ERROR);
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		printf("%s\n", new_pwd);
	return (EXIT_SUCCESS);
}
