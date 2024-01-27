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
	// t_list_d	*node;

	if (is_absolute_path(path))
	{
		cmpnt_list = ft_lstnew_d("");
		if (!cmpnt_list)
			return (NULL);
	}
	cmpnt = ft_strtok(path, "/");
	while (cmpnt)
	{
		if (!ft_lstnew_back_d(&cmpnt_list, cmpnt))
			return (ft_lstclear_d(&cmpnt_list, NULL), NULL);
		cmpnt = ft_strtok(NULL, "/");
	}
	return (cmpnt_list);
}

size_t	get_path_len_from_cmpnt_list(t_list_d *cmpnt_list)
{
	size_t	len;

	len = 0;
	while (cmpnt_list)
	{
		len += ft_strlen(cmpnt_list->content) + 1;
		cmpnt_list = cmpnt_list->next;
	}
	return (len);
}

size_t	get_path_len_from_cmpnt_node(t_list_d *cmpnt_node)
{
	size_t	len;

	len = 0;
	while (cmpnt_node)
	{
		len += ft_strlen(cmpnt_node->content) + 1;
		cmpnt_node = cmpnt_node->prev;
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
	while (cmpnt_list)
	{
		len = ft_strlen(cmpnt_list->content);
		ft_memcpy(&path[i], cmpnt_list->content, len);
		i += len;
		path[i++] = '/';
		cmpnt_list = cmpnt_list->next;
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
	len = get_path_len_from_cmpnt_node(cmpnt_node);
	path = (char *)malloc((len + 1) * sizeof(char));
	if (!path)
		return (NULL);
	i = 0;
	while (cmpnt_list)
	{
		len = ft_strlen(cmpnt_list->content);
		ft_memcpy(&path[i], cmpnt_list->content, len);
		i += len;
		path[i++] = '/';
		if (cmpnt_list == cmpnt_node)
			break ;
		cmpnt_list = cmpnt_list->next;
	}
	path[i] = '\0';
	return (path);
}
