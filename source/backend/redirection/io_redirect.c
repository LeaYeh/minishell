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
#include "expander.h"
#include "utils.h"
#include "clean.h"

int	expand_filename(t_shell *shell, char **filename)
{
	t_list		*expanded_list;
	int			ret;

	expanded_list = NULL;
	ret = expander(*filename, &expanded_list, shell, E_EXPAND | E_RM_QUOTES);
	if (ret == MALLOC_ERROR || ret == BAD_SUBSTITUTION)
		return (ft_lstclear(&expanded_list, free), ret);
	if (ft_lstsize_non_null(expanded_list) != 1)
	{
		ft_dprintf(2, ERROR_AMBIGUOUS_REDIRECT, PROGRAM_NAME, *filename);
		return (ft_lstclear(&expanded_list, free), AMBIGUOUS_REDIR);
	}
	free(*filename);
	*filename = expanded_list->content;
	ft_lstclear(&expanded_list, NULL);
	return (SUCCESS);
}

bool	handle_red_in(int *read_fd, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: ", PROGRAM_NAME, filename);
		perror("");
		return (false);
	}
	replace_fd(&fd, read_fd);
	return (true);
}

bool	handle_red_out(int *write_fd, char *filename, int o_flags)
{
	int	fd;

	fd = open(filename, o_flags, (S_IRUSR + S_IWUSR) | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		ft_dprintf(2, "%s: %s: ", PROGRAM_NAME, filename);
		perror("");
		return (false);
	}
	replace_fd(&fd, write_fd);
	return (true);
}

bool	handle_redirect_by_type(int *read_fd, int *write_fd, t_io_red *io_red)
{
	if (io_red->type == T_RED_IN || io_red->type == T_HERE_DOC)
		return (handle_red_in(read_fd, io_red->filename));
	else if (io_red->type == T_RED_OUT)
		return (handle_red_out(write_fd,
				io_red->filename, O_CREAT | O_RDWR | O_TRUNC));
	else if (io_red->type == T_APPEND)
		return (handle_red_out(write_fd,
				io_red->filename, O_CREAT | O_RDWR | O_APPEND));
	return (true);
}

int	handle_io_redirect(
	t_shell *shell, int *read_fd, int *write_fd, t_list *io_red_list)
{
	t_io_red	*io_red;
	int			ret;

	if (ft_lstsize_non_null(io_red_list) == 0)
		return (SUCCESS);
	while (io_red_list)
	{
		io_red = io_red_list->content;
		if (io_red->type != T_HERE_DOC)
		{
			ret = expand_filename(shell, &io_red->filename);
			if (ret != SUCCESS)
				return (ret);
		}
		if (!handle_redirect_by_type(read_fd, write_fd, io_red_list->content))
			return (GENERAL_ERROR);
		io_red_list = io_red_list->next;
	}
	return (SUCCESS);
}
