/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:59:29 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/20 19:38:24 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

// typedef struct s_cmpnt_node
// {
// 	char			*path;
// }	t_cmpnt_node;

// bool	fill_cmpnt_path(char **path)
// {

// }

// path has to be duplicated outside, and only free'd once cmpnt_list is not needed anymore.
t_list_d	*create_component_list(char *path)
{
	char		*cmpnt;
	t_list_d	*cmpnt_list;
	char		*tmp;
	// t_list_d	*node;

	path = ft_strdup(path);
	if (!path)
		return (NULL);
	cmpnt_list = NULL;
	if (is_absolute_path(path))
	{
		tmp = ft_strdup("");
		if (!tmp || !ft_lstnew_back_d(&cmpnt_list, tmp))
			return (free(path), free(tmp), NULL);
		if (path[1] == '/' && path[2] != '/')
		{
			tmp = ft_strdup("");
			if (!tmp || !ft_lstnew_back_d(&cmpnt_list, tmp))
				return (free(path), free(tmp), NULL);
		}

	}
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

bool	is_root_cmpnt(t_list_d *cmpnt_node)
{
	if (ft_strcmp(cmpnt_node->content, "") == 0)
		return (true);
	return (false);
}

size_t	get_path_len_from_cmpnt_list(t_list_d *cmpnt_list)
{
	size_t	len;

	len = 0;
	while (cmpnt_list && is_root_cmpnt(cmpnt_list))
	{
		len++;
		cmpnt_list = cmpnt_list->next;
	}
	while (cmpnt_list)
	{
		len += ft_strlen(cmpnt_list->content);
		cmpnt_list = cmpnt_list->next;
		if (cmpnt_list)
			len++;
	}
	return (len);
}

size_t	get_path_len_from_cmpnt_node(t_list_d *cmpnt_list, t_list_d *cmpnt_node)
{
	size_t	len;

	len = 0;
	while (cmpnt_list && cmpnt_list->prev != cmpnt_node && \
		is_root_cmpnt(cmpnt_list))
	{
		len++;
		cmpnt_list = cmpnt_list->next;
	}
	while (cmpnt_list && cmpnt_list->prev != cmpnt_node)
	{
		len += ft_strlen(cmpnt_list->content);
		cmpnt_list = cmpnt_list->next;
		if (cmpnt_list)
			len++;
	}
	return (len);
}

char	*convert_cmpnt_list_to_path(t_list_d *cmpnt_list)
{
	size_t	i;
	size_t	len;
	char	*path;

	//TODO: How to know if root or not?
	len = get_path_len_from_cmpnt_list(cmpnt_list);
	path = (char *)malloc((len + 1) * sizeof(char));
	if (!path)
		return (NULL);
	i = 0;
	// Name: handle_root()
	while (cmpnt_list && is_root_cmpnt(cmpnt_list))
	{
		path[i++] = '/';
		cmpnt_list = cmpnt_list->next;
	}
	while (cmpnt_list)
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

char	*convert_cmpnt_node_to_path(t_list_d *cmpnt_list, t_list_d *cmpnt_node)
{
	size_t	i;
	size_t	len;
	char	*path;

	//TODO: How to know if root or not?
	len = get_path_len_from_cmpnt_node(cmpnt_list, cmpnt_node);
	path = (char *)malloc((len + 1) * sizeof(char));
	if (!path)
		return (NULL);
	i = 0;
	while (cmpnt_list && cmpnt_list->prev != cmpnt_node && \
		is_root_cmpnt(cmpnt_list))
	{
		path[i++] = '/';
		cmpnt_list = cmpnt_list->next;
	}
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
