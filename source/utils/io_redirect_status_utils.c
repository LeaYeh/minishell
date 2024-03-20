/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_status_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:49:36 by lyeh              #+#    #+#             */
/*   Updated: 2024/02/17 23:49:38 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	get_redirect_type_from_list(t_list *io_red_list)
{
	t_io_red	*io_red;

	if (!io_red_list)
		return (T_NONE);
	io_red = io_red_list->content;
	return (io_red->type);
}
