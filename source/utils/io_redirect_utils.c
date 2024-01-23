/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 19:44:52 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/06 20:23:24 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

t_io_red	*init_io_red(void)
{
	t_io_red	*io_red;

	io_red = (t_io_red *)malloc(sizeof(t_io_red));
	if (!io_red)
		return (NULL);
	io_red->type = T_NONE;
	io_red->in_file = NULL;
	io_red->out_file = NULL;
	io_red->here_end = NULL;
	return (io_red);
}

void	free_io_red(t_io_red *io_red)
{
	free(io_red->in_file);
	free(io_red->out_file);
	free(io_red->here_end);
	free(io_red);
}
