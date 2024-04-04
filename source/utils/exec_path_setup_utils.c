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

#include "utils.h"

static bool	set_path_list(t_list **path_list, char *env[]);
static bool	append_path(t_list **path_list, char *path, char *colon);
static bool	find_exec_path(char **exec_path, t_list *path_list, char *cmd_name);
static bool	confirm_exec_path(char **exec_path, char **tmp);

bool	set_exec_path(char **exec_path, char *cmd_name, char *env[])
{
	t_list	*path_list;

	if (ft_strchr(cmd_name, '/'))
		return ((*exec_path = ft_strdup(cmd_name)) != NULL);
	if (!set_path_list(&path_list, env))
		return (false);
	if (!path_list)
		return ((*exec_path = ft_strdup(cmd_name)) != NULL);
	if (!find_exec_path(exec_path, path_list, cmd_name))
		return (ft_lstclear(&path_list, free), false);
	return (ft_lstclear(&path_list, free), true);
}

static bool	set_path_list(t_list **path_list, char *env[])
{
	char	*colon;
	char	*path;

	*path_list = NULL;
	path = get_value_from_env(env, "PATH");
	if (!path)
		return (true);
	while (true)
	{
		colon = ft_strchr(path, ':');
		if (!append_path(path_list, path, colon))
			return (ft_lstclear(path_list, free), false);
		if (!colon)
			break ;
		path = colon + 1;
	}
	return (true);
}

static bool	append_path(t_list **path_list, char *path, char *colon)
{
	int		len;
	char	*path_part;

	if (colon)
		len = colon - path;
	else
		len = ft_strlen(path);
	if (len != 0)
		path_part = ft_strndup(path, len);
	else
		path_part = ft_strdup(".");
	if (!path_part)
		return (false);
	return (ft_lstnew_back(path_list, path_part));
}

static bool	find_exec_path(char **exec_path, t_list *path_list, char *cmd_name)
{
	int		cmd_name_len;
	int		exec_path_len;
	char	*tmp;

	cmd_name_len = ft_strlen(cmd_name);
	tmp = NULL;
	while (path_list)
	{
		exec_path_len = ft_strlen(path_list->content) + 1 + cmd_name_len;
		tmp = (char *)malloc(exec_path_len + 1);
		if (!tmp)
			return (false);
		ft_snprintf(tmp, exec_path_len + 1, "%s/%s",
			path_list->content, cmd_name);
		if (confirm_exec_path(exec_path, &tmp))
			return (true);
		path_list = path_list->next;
	}
	return (true);
}

static bool	confirm_exec_path(char **exec_path, char **tmp)
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
