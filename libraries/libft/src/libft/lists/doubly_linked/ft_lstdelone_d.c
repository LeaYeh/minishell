/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:04:26 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/23 21:10:37 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone_d(t_list_d *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (del != NULL && lst->content != NULL)
		(*del)(lst->content);
	free(lst);
	return ;
}
