/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:18 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/01 19:32:19 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "clean.h"

bool	handle_red_in(t_final_cmd_table *final_cmd_table, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: ", PROGRAM_NAME, filename);
		perror("");
		return (false);
	}
	replace_fd(&fd, &final_cmd_table->read_fd);
	return (true);
}

bool	handle_red_out(
	t_final_cmd_table *final_cmd_table, char *filename, int o_flags)
{
	int	fd;

	fd = open(filename, o_flags, (S_IRUSR + S_IWUSR) | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: ", PROGRAM_NAME, filename);
		perror("");
		return (false);
	}
	replace_fd(&fd, &final_cmd_table->write_fd);
	return (true);
}

bool	handle_redirect_by_type(
	t_final_cmd_table *final_cmd_table, t_io_red *io_red)
{
	if (io_red->type == T_RED_IN || io_red->type == T_HERE_DOC)
		return (handle_red_in(final_cmd_table, io_red->in_file));
	else if (io_red->type == T_RED_OUT)
		return (handle_red_out(
				final_cmd_table, io_red->out_file, O_CREAT | O_RDWR | O_TRUNC));
	else if (io_red->type == T_APPEND)
		return (handle_red_out(
				final_cmd_table,
				io_red->out_file, O_CREAT | O_RDWR | O_APPEND));
	return (true);
}

bool	handle_io_redirect(
	t_final_cmd_table *final_cmd_table, t_list *io_red_node)
{
	if (ft_lstsize_non_null(io_red_node) == 0)
		return (true);
	while (io_red_node)
	{
		if (!handle_redirect_by_type(final_cmd_table, io_red_node->content))
		{
			// safe_close(&final_cmd_table->read_fd);
			// safe_close(&final_cmd_table->write_fd);
			return (false);
		}
		io_red_node = io_red_node->next;
	}
	return (true);
}
