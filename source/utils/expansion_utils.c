/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 01:17:55 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/18 18:27:50 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

int	expand_list(
		t_sh *shell,
		t_list *list,
		t_list **expanded_list,
		t_expd_op op_mask)
{
	int		ret;
	t_list	*tmp_list;

	ret = SUCCESS;
	while (list)
	{
		tmp_list = NULL;
		ret = expander(list->content, &tmp_list, shell, op_mask);
		if (ret != SUCCESS)
		{
			ft_lstclear(&tmp_list, free);
			break ;
		}
		else
			ft_lstadd_back(expanded_list, tmp_list);
		list = list->next;
	}
	return (ret);
}
