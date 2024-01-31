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

char	*get_value_with_key(char *str, char *key)
{
	int		key_len;
	char	*value;

	if (!str || !key)
		return (NULL);
	key_len = ft_strlen(key);
	if (ft_strncmp(str, key, key_len) == 0 && str[key_len] == '=')
	{
		value = str + key_len + 1;
		return (value);
	}
	return (NULL);
}

char	*get_value_from_env(char **envp, char *key)
{
	int		i;
	char	*value;

	if (!envp || !key)
		return (NULL);
	value = NULL;
	i = 0;
	while (envp[i])
	{
		value = get_value_with_key(envp[i], key);
		if (value)
			break ;
		i++;
	}
	return (value);
}

char	*get_base_filename(char	*full_name)
{
	char	*ret;
	char	**tmp;
	int		array_len;

	tmp = ft_split(full_name, '/');
	if (!tmp)
		return (NULL);
	array_len = get_array_len(tmp);
	if (array_len > 0)
		ret = ft_strdup(tmp[array_len - 1]);
	else
		ret = NULL;
	free_array(&tmp);
	return (ret);
}

bool	set_all_path(char ***all_path, char **envp)
{
	char	*path_value;

	path_value = get_value_from_env(envp, "PATH");
	if (!path_value)
		return (NULL);
	*all_path = ft_split(path_value, ':');
	if (!*all_path)
		return (false);
	return (true);
}

char	*set_exec_path(char *exec_path, char *cmd_name, char **envp)
{
	char	exec_path[FILENAME_MAX];
	char	**all_path;
	int		i;

	if (!cmd_name)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
		return (ft_strdup(cmd_name));
	if (!set_all_path(&all_path, envp))
		return (NULL);
	if (!all_path)
		return (NULL);
	i = 0;
	while (all_path[i])
	{
		sprintf(exec_path, "%s/%s", all_path[i], cmd_name);
		if (access(exec_path, F_OK) == 0)
			break ;
		i++;
	}
	if (i == get_array_len(all_path))
		return (free_array(&all_path), ft_strdup(cmd_name));
	return (free_array(&all_path), ft_strdup(exec_path));
}

// char	*get_exec_path(char *cmd_name, char **envp)
// {
// 	char	**all_path;
// 	char	*part_path;
// 	char	*exec_path;
// 	int		i;

// 	if (ft_strchr(cmd_name, '/') && access(cmd_name, F_OK) == 0)
// 		return (ft_strdup(cmd_name));
// 	exec_path = get_value_from_env(envp, "PATH");
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
