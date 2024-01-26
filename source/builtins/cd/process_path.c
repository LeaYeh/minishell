/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 02:29:11 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/26 02:30:23 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	set_final_path(char **final_path, char **new_pwd, char *target_dir)
{
	char	*pwd;
	int		ret;

	// get_value_from_env(env_list, "PWD")
	// if is_abs_path() -> use it
	// else -> getcwd()
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (handle_getcwd_error(errno, target_dir));
	ret = simplify_path(new_pwd, pwd, target_dir);
	if (ret != SUCCESS)
		return (free(pwd), ret);
	*final_path = try_to_convert_abs_to_rel_path(*new_pwd, pwd);
	free(pwd);
	if (!*final_path || !ensure_path_not_empty(final_path))
		return (free(*new_pwd), GENERAL_ERROR);
	return (SUCCESS);
}

int	simplify_path(char **new_pwd, char *pwd, char *target_dir)
{
	t_list_d	*cmpnt_list;
	int			ret;

	cmpnt_list = get_abs_path_cmpnt_list(pwd, target_dir);
	if (!cmpnt_list)
		return (GENERAL_ERROR);
	ret = handle_dot_cmpnts(&cmpnt_list, target_dir);
	if (ret != SUCCESS)
		return (ft_lstclear_d(&cmpnt_list, free), ret);
	*new_pwd = convert_cmpnt_node_to_path(cmpnt_list, ft_lstlast_d(cmpnt_list));
	ft_lstclear_d(&cmpnt_list, free);
	if (!*new_pwd)
		return (GENERAL_ERROR);
	return (SUCCESS);
}

//TODO: Doesn't necessarily need an absolute path, so maybe adjust the function name
char	*try_to_convert_abs_to_rel_path(char *abs_path, char *pwd)
{
	size_t	abs_path_len;
	size_t	pwd_len;
	char	*rel_path;

	if (!is_abs_path(pwd) || !is_abs_path(abs_path))
		return (ft_strdup(abs_path));
	abs_path_len = ft_strlen(abs_path);
	// Can pwd be NULL?
	pwd_len = ft_strlen(pwd);
	if (abs_path_len < pwd_len || \
		ft_strncmp(abs_path, pwd, pwd_len) != 0 || \
		(abs_path[pwd_len] != '/' && abs_path[pwd_len] != '\0'))
		return (ft_strdup(abs_path));
	// Else if they are equal, return "."
	// else if (abs_path_len == pwd_len)
	// 	rel_path = ft_strdup(".");
	else
		rel_path = ft_substr(abs_path, pwd_len + 1, abs_path_len - pwd_len);
	return (rel_path);
}
