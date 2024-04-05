/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cmpnts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:34:59 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/26 02:12:59 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static void	rm_dot_cmpnts(t_list_d **cmpnt_list);
static int	rm_dotdot_cmptnts(t_list_d **cmpnt_list, char *target_dir);

int	handle_dot_cmpnts(t_list_d **cmpnt_list, char *target_dir)
{
	int	ret;

	rm_dot_cmpnts(cmpnt_list);
	ret = rm_dotdot_cmptnts(cmpnt_list, target_dir);
	return (ret);
}

static void	rm_dot_cmpnts(t_list_d **cmpnt_list)
{
	t_list_d	*cur;

	cur = *cmpnt_list;
	while (cur)
	{
		if (ft_strcmp(cur->content, ".") == 0)
			ft_lstdrop_node_d(cmpnt_list, &cur, free);
		else
			cur = cur->next;
	}
}

static int	rm_dotdot_cmptnts(t_list_d **cmpnt_list, char *target_dir)
{
	t_list_d	*cur;
	t_list_d	*prev;
	int			ret;

	if (!*cmpnt_list)
		return (SUCCESS);
	cur = (*cmpnt_list)->next;
	while (cur)
	{
		prev = cur->prev;
		if (prev && ft_strcmp(cur->content, "..") == 0)
		{
			ret = check_cmpnt_node_path(*cmpnt_list, prev, target_dir);
			if (ret != SUCCESS)
				return (ret);
			ft_lstdrop_node_d(cmpnt_list, &cur, free);
			if (prev->prev)
				ft_lstdrop_node_d(cmpnt_list, &prev, free);
		}
		else
			cur = cur->next;
	}
	return (SUCCESS);
}
