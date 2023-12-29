/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 19:44:52 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/29 16:15:26 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

t_io_red	*init_io_red(void)
{
	t_io_red	*io_red;

	io_red = (t_io_red *)malloc(sizeof(t_io_red));
	if (!io_red)
		return (NULL);
	io_red->in_file = NULL;
	io_red->out_file = NULL;
	io_red->here_end = NULL;
	io_red->red_in = STDIN_FILENO;
	io_red->red_out = STDOUT_FILENO;
	return (io_red);
}

void	free_io_red(t_io_red *io_red)
{
	ft_free_and_null((void **)&io_red->in_file);
	ft_free_and_null((void **)&io_red->out_file);
	ft_free_and_null((void **)&io_red->here_end);
	ft_free_and_null((void **)&io_red);
}
