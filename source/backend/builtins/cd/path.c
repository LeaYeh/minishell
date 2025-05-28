/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 02:29:11 by ldulling          #+#    #+#             */
/*   Updated: 2025/05/29 00:30:03 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static int	simplify_path(char **new_path, char *target_dir, char *cwd);
static char	*try_to_convert_abs_to_rel_path(char *abs_path, char *cwd);

int	set_final_path(char **final_path, char **new_pwd, char *target_dir)
{
	char	*cwd;
	int		ret;

	cwd = getcwd(NULL, 0);
	if (!cwd && errno == ENOMEM)
		return (handle_cd_error(errno, target_dir));
	ret = simplify_path(new_pwd, target_dir, cwd);
	if (ret != SUCCESS)
		return (free(cwd), ret);
	*final_path = try_to_convert_abs_to_rel_path(*new_pwd, cwd);
	free(cwd);
	if (!*final_path)
		return (free(*new_pwd), MALLOC_ERROR);
	if (ft_strlen(*final_path) + 1 > PATH_MAX)
	{
		free(*final_path);
		ret = simplify_path(final_path, target_dir, NULL);
		if (ret != SUCCESS)
			return (free(*new_pwd), ret);
	}
	if (!ensure_path_not_empty(final_path))
		return (free(*new_pwd), MALLOC_ERROR);
	return (SUCCESS);
}

static int	simplify_path(char **new_path, char *target_dir, char *cwd)
{
	t_list_d	*cmpnt_list;
	int			ret;

	if (cwd)
		cmpnt_list = get_abs_path_cmpnt_list(cwd, target_dir);
	else
		cmpnt_list = create_cmpnt_list(target_dir);
	if (!cmpnt_list)
		return (MALLOC_ERROR);
	ret = handle_dot_cmpnts(&cmpnt_list, target_dir);
	if (ret != SUCCESS)
		return (ft_lstclear_d(&cmpnt_list, free), ret);
	*new_path = convert_cmpnt_node_to_path(
			cmpnt_list, ft_lstlast_d(cmpnt_list));
	ft_lstclear_d(&cmpnt_list, free);
	if (!*new_path)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

static char	*try_to_convert_abs_to_rel_path(char *abs_path, char *cwd)
{
	int		abs_path_len;
	int		pwd_len;
	char	*rel_path;

	if (!is_abs_path(cwd) || !is_abs_path(abs_path))
		return (ft_strdup(abs_path));
	abs_path_len = ft_strlen(abs_path);
	pwd_len = ft_strlen(cwd);
	if (abs_path_len < pwd_len || \
		ft_strncmp(abs_path, cwd, pwd_len) != 0 || \
		(abs_path[pwd_len] != '/' && abs_path[pwd_len] != '\0'))
		return (ft_strdup(abs_path));
	else
		rel_path = ft_substr(abs_path, pwd_len + 1, abs_path_len - pwd_len);
	return (rel_path);
}
