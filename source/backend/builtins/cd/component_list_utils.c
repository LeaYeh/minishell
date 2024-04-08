/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmpnt_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:59:29 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/21 17:38:30 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	check_cmpnt_node_path(
		t_list_d *cmpnt_list, t_list_d *cmpnt_node, char *target_dir)
{
	char	*path;

	path = convert_cmpnt_node_to_path(cmpnt_list, cmpnt_node);
	if (!path)
		return (BUILTIN_ERROR);
	if (ft_strlen(path) + 1 <= PATH_MAX)
	{
		if (!check_dir(path, target_dir))
			return (free(path), GENERAL_ERROR);
	}
	else
		if (!check_dir(target_dir, target_dir))
			return (free(path), GENERAL_ERROR);
	return (free(path), SUCCESS);
}

int	get_path_len_from_cmpnt_node(
		t_list_d *cmpnt_list, t_list_d *cmpnt_node)
{
	int	len;

	len = 0;
	while (cmpnt_list && cmpnt_list->prev != cmpnt_node && \
		is_root_cmpnt_node(cmpnt_list))
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

bool	is_root_cmpnt_node(t_list_d *cmpnt_node)
{
	if (ft_strcmp(cmpnt_node->content, "") == 0)
		return (true);
	return (false);
}
