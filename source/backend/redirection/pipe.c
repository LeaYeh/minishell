/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:18:11 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/08 15:28:15 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "clean.h"

void	close_cmd_table_pipe(t_cmd_table *cmd_table_node)
{
	safe_close(&cmd_table_node->pipe_read_fd);
	safe_close(&cmd_table_node->pipe_write_fd);
	safe_close(&cmd_table_node->pipe_fd[0]);
	safe_close(&cmd_table_node->pipe_fd[1]);
}

bool	create_pipe(t_cmd_table *cmd_table_node)
{
	if (pipe(cmd_table_node->pipe_fd) == -1)
		return (false);
	return (true);
}

// If the pipe is not set up, it will return false
bool	setup_pipe(t_cmd_table *cur_cmd_table, t_cmd_table *target_cmd_table)
{
	if (cur_cmd_table->pipe_fd[0] == -1 || cur_cmd_table->pipe_fd[1] == -1)
		return (false);
	target_cmd_table->pipe_read_fd = cur_cmd_table->pipe_fd[0];
	cur_cmd_table->pipe_write_fd = cur_cmd_table->pipe_fd[1];
	return (true);
}

bool	setup_subshell_pipe(t_list_d *cmd_table_node)
{
	t_cmd_table	*cur_cmd_table;
	t_cmd_table	*target_cmd_table;
	int			level;

	cur_cmd_table = cmd_table_node->content;
	level = cur_cmd_table->subshell_level;
	while (level > 0)
	{
		if (get_cmd_table_type_from_list(cmd_table_node) == C_SUBSHELL_END)
		{
			cmd_table_node = cmd_table_node->next;
			if (get_cmd_table_type_from_list(cmd_table_node) == C_PIPE)
			{
				target_cmd_table = cmd_table_node->next->content;
				return (setup_pipe(cur_cmd_table, target_cmd_table));
			}
			level--;
		}
		if (get_cmd_table_type_from_list(cmd_table_node) == C_SUBSHELL_START)
			level++;
		cmd_table_node = cmd_table_node->next;
	}
	return (true);
}

// TODO: Need to check with subshell
bool	set_normal_pipe_target(t_list **target_list, t_list_d *cmd_table_node)
{
	int		cur_level;
	int		target_level;

	cmd_table_node = cmd_table_node->next;
	if (get_cmd_table_type_from_list(cmd_table_node) == C_SUBSHELL_START)
	{
		cmd_table_node = cmd_table_node->next;
		cur_level = ((t_cmd_table *)cmd_table_node->content)->subshell_level;
		while (true)
		{
			target_level = \
				((t_cmd_table *)cmd_table_node->content)->subshell_level;
			if (target_level < cur_level)
				break ;
			if (get_cmd_table_type_from_list(cmd_table_node) == C_SIMPLE_CMD)
				if (!ft_lstnew_back(target_list, cmd_table_node))
					return (false);
			cmd_table_node = cmd_table_node->next;
		}
	}
	else if (!ft_lstnew_back(target_list, cmd_table_node))
		return (false);
	return (true);
}

bool	setup_normal_pipe(t_list_d *cmd_table_node)
{
	t_cmd_table	*cur_cmd_table;
	t_cmd_table	*target_cmd_table;
	t_list		*target_list;

	cur_cmd_table = cmd_table_node->content;
	cmd_table_node = cmd_table_node->next;
	if (get_cmd_table_type_from_list(cmd_table_node) == C_PIPE)
	{
		if (create_pipe(cur_cmd_table))
			return (false);
		target_list = NULL;
		if (!set_normal_pipe_target(&target_list, cmd_table_node))
			return (ft_lstclear(&target_list, (void *)free_cmd_table), false);
		while (target_list)
		{
			target_cmd_table = target_list->content;
			if (!setup_pipe(cur_cmd_table, target_cmd_table))
				return (false);
			target_list = target_list->next;
		}
	}
	return (true);
}
