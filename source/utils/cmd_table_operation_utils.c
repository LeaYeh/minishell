/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_operation_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:30:35 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/14 15:20:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

void	free_cmd_table(t_cmd_table *cmd_table)
{
	free(cmd_table->cmd_name);
	ft_lstclear(&cmd_table->cmd_args, free);
	ft_lstclear(&cmd_table->assignment_list, free);
	ft_lstclear(&cmd_table->io_red_list, (void *)free_io_red);
	free(cmd_table);
}

t_cmd_table	*init_cmd_table(void)
{
	t_cmd_table	*cmd_table;

	cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	if (!cmd_table)
		return (NULL);
	cmd_table->id = 0;
	cmd_table->subshell_level = 0;
	cmd_table->pipe_fd[0] = -1;
	cmd_table->pipe_fd[1] = -1;
	cmd_table->pipe_read_fd = -1;
	cmd_table->pipe_write_fd = -1;
	cmd_table->type = C_NONE;
	cmd_table->assignment_list = NULL;
	cmd_table->cmd_name = NULL;
	cmd_table->cmd_args = NULL;
	cmd_table->io_red_list = NULL;
	return (cmd_table);
}

t_cmd_table	*get_cmd_table_from_list(t_list_d *cmd_table_node)
{
	if (!cmd_table_node || !cmd_table_node->content)
		return (NULL);
	return (cmd_table_node->content);
}

bool	append_cmd_table_by_scenario(int token_type, t_list_d **cmd_table_list)
{
	t_cmd_table	*cmd_table;

	if (*cmd_table_list)
	{
		cmd_table = ft_lstlast_d(*cmd_table_list)->content;
		if (token_type == T_END || cmd_table->type == C_NONE)
			return (true);
		if (get_last_simple_cmd_table(*cmd_table_list) && \
			(is_io_red_op(token_type) || is_word(token_type)))
			return (true);
	}
	printf("[%s] Create new cmd_table\n", ft_get_token_type_str(token_type));
	return (append_empty_cmd_table(cmd_table_list));
}

bool	append_empty_cmd_table(t_list_d **cmd_table_list)
{
	t_list_d	*cmd_table_node;
	t_list_d	*last_node;
	t_cmd_table	*cmd_table;

	cmd_table = init_cmd_table();
	if (!cmd_table)
		return (false);
	last_node = ft_lstlast_d(*cmd_table_list);
	if (!last_node)
		cmd_table->id = 0;
	else
		cmd_table->id = ((t_cmd_table *)last_node->content)->id + 1;
	cmd_table_node = ft_lstnew_d(cmd_table);
	if (!cmd_table_node)
		return (free_cmd_table(cmd_table), false);
	ft_lstadd_back_d(cmd_table_list, cmd_table_node);
	return (true);
}
