/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:05:20 by codespace         #+#    #+#             */
/*   Updated: 2024/05/26 23:11:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "clean.h"
#include "utils.h"

int	exec_cd(t_sh *shell, char *args[], t_list **env_list)
{
	char	*final_path;
	int		ret;
	char	*target_dir;

	target_dir = get_target_dir(args, *env_list);
	if (!target_dir)
		return (GENERAL_ERROR);
	ret = set_final_path(
			&final_path, (char **)&shell->builtin_allocation, target_dir);
	if (ret != SUCCESS)
		return (ret);
	if (chdir(final_path) == -1)
		return (free(final_path), ft_free_and_null(&shell->builtin_allocation),
			handle_cd_error(errno, target_dir));
	free(final_path);
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		ft_printf("%s\n", target_dir);
	if (!update_pwd_env(env_list, (char **)&shell->builtin_allocation))
		return (ft_free_and_null(&shell->builtin_allocation), MALLOC_ERROR);
	return (EXIT_SUCCESS);
}
