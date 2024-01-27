/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_components.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:34:59 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/20 19:42:45 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
// #include "clean.h"
// #include "minishell.h"

// bool	is_dotdot(char *str, size_t i)
// {
// 	if (ft_strnstr(str, ".."))
// 	{

// 	}
// }

// bool	handle_dotdot(char **str)
// {

// }

bool	is_dot_component(char *directory)
{
	if (ft_strncmp(directory, ".", 2) == 0 || ft_strncmp(directory, "..", 3) == 0 || \
		ft_strncmp(directory, "./", 3) == 0 || ft_strncmp(directory, "../", 4) == 0)
		return (true);
	return (false);
}

void	rm_dot_cmpnts(t_list_d **cmpnt_list)
{
	t_list_d	*cur;

	cur = *cmpnt_list;
	while (cur)
	{
		if (ft_strcmp(cur->content, ".") == 0)
			ft_lstdrop_node_d(cmpnt_list, &cur, NULL);
		else
			cur = cur->next;
	}
}

// It has to be a linked list in order to easily remove components.
// Have one malloced string and store pointers to the end of each component.
// When I need the path, replace the char the ptr points to with \0, check the path, then revert again.
// I have to create a new string out of the cmpnt_list for that, otherwise there could be multiple slashes in the original string.
bool	rm_dotdot_cmptnts(t_list_d **cmpnt_list, char *og_path)
{
	t_list_d	*cur;
	char		*cleaned_path;
	t_list_d	*prev;

	if (!*cmpnt_list)
		return (true);
	cur = (*cmpnt_list)->next;
	while (cur)
	{
		prev = cur->prev;
		if (prev && ft_strcmp(cur->content, "..") == 0 && \
			ft_strcmp(prev->content, "..") != 0 && \
			ft_strcmp(prev->content, "") != 0)
		{
			cleaned_path = convert_cmpnt_node_to_path(*cmpnt_list, prev);
			if (!cleaned_path)
				return (false);
			if (!check_directory(cleaned_path, og_path))
				return (free(cleaned_path), true);
			free(cleaned_path);
			ft_lstdrop_node_d(cmpnt_list, &cur, NULL);
			ft_lstdrop_node_d(cmpnt_list, &prev, NULL);
		}
		else
			cur = cur->next;
	}
	return (true);
}
