/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:56:26 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/18 23:11:12 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

bool	set_all_path(char ***all_path, char *env[])
{
	char	*path_value;

	path_value = get_value_from_env(env, "PATH");
	if (!path_value)
		return (*all_path = NULL, true);
	*all_path = ft_split(path_value, ':');
	if (!*all_path)
		return (false);
	return (true);
}

bool	confirm_exec_path(char **exec_path, char **tmp)
{
	if (access(*tmp, X_OK) == 0 && !is_dir(*tmp))
	{
		free(*exec_path);
		*exec_path = *tmp;
		return (true);
	}
	else if (!*exec_path && access(*tmp, F_OK) == 0 && !is_dir(*tmp))
		*exec_path = *tmp;
	else
		ft_free_and_null((void **)tmp);
	return (false);
}

bool	find_exec_path(char **exec_path, char *all_path[], char *cmd_name)
{
	int		cmd_name_len;
	int		exec_path_len;
	int		i;
	char	*tmp;

	cmd_name_len = ft_strlen(cmd_name);
	tmp = NULL;
	i = 0;
	while (all_path[i])
	{
		exec_path_len = ft_strlen(all_path[i]) + 1 + cmd_name_len;
		tmp = (char *)malloc(exec_path_len + 1);
		if (!tmp)
			return (false);
		ft_snprintf(tmp, exec_path_len + 1, "%s/%s", all_path[i], cmd_name);
		if (confirm_exec_path(exec_path, &tmp))
			return (true);
		i++;
	}
	return (true);
}

bool	set_exec_path(char **exec_path, char *cmd_name, char *env[])
{
	char	**all_path;

	if (ft_strchr(cmd_name, '/'))
		return ((*exec_path = ft_strdup(cmd_name)) != NULL);
	if (!set_all_path(&all_path, env))
		return (false);
	if (!all_path)
		return ((*exec_path = ft_strdup(cmd_name)) != NULL);
	if (!find_exec_path(exec_path, all_path, cmd_name))
		return (free_array(&all_path), false);
	return (free_array(&all_path), true);
}

// char	*get_exec_path(char *cmd_name, char *env[])
// {
// 	char	**all_path;
// 	char	*part_path;
// 	char	*exec_path;
// 	int		i;

// 	if (ft_strchr(cmd_name, '/') && access(cmd_name, F_OK) == 0)
// 		return (ft_strdup(cmd_name));
// 	exec_path = get_value_from_env(env, "PATH");
// 	all_path = ft_split(exec_path, ':');
// 	ft_free_and_null((void **)&exec_path);
// 	i = 0;
// 	while (all_path && all_path[i])
// 	{
// 		part_path = ft_strjoin(all_path[i], "/");
// 		exec_path = ft_strjoin(part_path, cmd_name);
// 		ft_free_and_null((void **)&part_path);
// 		if (access(exec_path, F_OK) == 0)
// 			break ;
// 		ft_free_and_null((void **)&exec_path);
// 		i++;
// 	}
// 	free_array(&all_path, -1);
// 	return (exec_path);
// }
