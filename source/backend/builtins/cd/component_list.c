/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmpnt_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 02:18:36 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/26 02:24:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static bool	create_root_cmpnt_nodes(t_list_d **cmpnt_list, char *path);
static void	convert_root_cmpnt_nodes_to_path(
				t_list_d **cmpnt_list,
				t_list_d *cmpnt_node,
				char *path,
				int *i);

t_list_d	*get_abs_path_cmpnt_list(char *pwd, char *target_dir)
{
	t_list_d	*cmpnt_list;
	t_list_d	*tmp_list;

	cmpnt_list = NULL;
	if (!is_abs_path(target_dir))
	{
		cmpnt_list = create_cmpnt_list(pwd);
		if (!cmpnt_list)
			return (NULL);
	}
	if (*target_dir)
	{
		tmp_list = create_cmpnt_list(target_dir);
		if (!tmp_list)
			return (ft_lstclear_d(&cmpnt_list, free), NULL);
		ft_lstadd_back_d(&cmpnt_list, tmp_list);
	}
	return (cmpnt_list);
}

t_list_d	*create_cmpnt_list(char *path)
{
	char		*cmpnt;
	t_list_d	*cmpnt_list;
	char		*tmp;

	path = ft_strdup(path);
	if (!path)
		return (NULL);
	cmpnt_list = NULL;
	if (is_abs_path(path))
		if (!create_root_cmpnt_nodes(&cmpnt_list, path))
			return (free(path), NULL);
	cmpnt = ft_strtok(path, "/");
	while (cmpnt)
	{
		tmp = ft_strdup(cmpnt);
		if (!tmp || !ft_lstnew_back_d(&cmpnt_list, tmp))
			return (free(path), free(tmp), ft_lstclear_d(&cmpnt_list, free),
				NULL);
		cmpnt = ft_strtok(NULL, "/");
	}
	return (free(path), cmpnt_list);
}

static bool	create_root_cmpnt_nodes(t_list_d **cmpnt_list, char *path)
{
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp || !ft_lstnew_back_d(cmpnt_list, tmp))
		return (free(tmp), false);
	if (path[1] == '/' && path[2] != '/')
	{
		tmp = ft_strdup("");
		if (!tmp || !ft_lstnew_back_d(cmpnt_list, tmp))
			return (free(tmp), false);
	}
	return (true);
}

char	*convert_cmpnt_node_to_path(
			t_list_d *cmpnt_list, t_list_d *cmpnt_node)
{
	int		i;
	int		len;
	char	*path;

	len = get_path_len_from_cmpnt_node(cmpnt_list, cmpnt_node);
	path = (char *)malloc((len + 1) * sizeof(char));
	if (!path)
		return (NULL);
	i = 0;
	convert_root_cmpnt_nodes_to_path(&cmpnt_list, cmpnt_node, path, &i);
	while (cmpnt_list && cmpnt_list->prev != cmpnt_node)
	{
		len = ft_strlen(cmpnt_list->content);
		ft_memcpy(&path[i], cmpnt_list->content, len);
		i += len;
		cmpnt_list = cmpnt_list->next;
		if (cmpnt_list)
			path[i++] = '/';
	}
	path[i] = '\0';
	return (path);
}

static void	convert_root_cmpnt_nodes_to_path(
				t_list_d **cmpnt_list,
				t_list_d *cmpnt_node,
				char *path,
				int *i)
{
	while (*cmpnt_list && (*cmpnt_list)->prev != cmpnt_node && \
		is_root_cmpnt_node(*cmpnt_list))
	{
		path[(*i)++] = '/';
		*cmpnt_list = (*cmpnt_list)->next;
	}
}
