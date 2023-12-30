/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:16:11 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/30 15:12:38 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "debug.h"

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
	cmd_table->type = C_NONE;
	cmd_table->assignment_list = NULL;
	cmd_table->cmd_name = NULL;
	cmd_table->cmd_args = NULL;
	cmd_table->io_red_list = NULL;
	return (cmd_table);
}

bool	append_empty_cmd_table(t_list_d **cmd_table_list)
{
	t_list_d	*cmd_table_node;
	t_cmd_table	*cmd_table;

	cmd_table = init_cmd_table();
	if (!cmd_table)
		return (false);
	cmd_table_node = ft_lstnew_d(cmd_table);
	if (!cmd_table_node)
		return (free_cmd_table(cmd_table), false);
	ft_lstadd_back_d(cmd_table_list, cmd_table_node);
	return (true);
}

t_cmd_table	*get_last_simple_cmd_table(t_list_d *cmd_table_list)
{
	t_list_d	*node;
	t_cmd_table	*last_simple_cmd_table;
	int			cur_type;

	node = cmd_table_list;
	last_simple_cmd_table = NULL;
	while (node && node->content)
	{
		cur_type = ((t_cmd_table *)node->content)->type;
		if (cur_type == C_PIPE || cur_type == C_AND || cur_type == C_OR)
			last_simple_cmd_table = NULL;
		if (cur_type == C_SIMPLE_CMD || cur_type == C_NONE)
			last_simple_cmd_table = node->content;
		node = node->next;
	}
	return (last_simple_cmd_table);
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
