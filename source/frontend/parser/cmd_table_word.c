/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:07:04 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/29 20:21:47 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	fill_cmd_name(t_token *token, t_cmd_table *cmd_table)
{
	char	*cmd_name;

	if (cmd_table->cmd_name != NULL)
		return (false);
	cmd_name = ft_strdup(token->data);
	if (!cmd_name)
		return (false);
	cmd_table->cmd_name = cmd_name;
	return (true);
}

bool	fill_cmd_args(t_token *token, t_cmd_table *cmd_table)
{
	char	*cmd_arg;
	t_list	*node;

	cmd_arg = ft_strdup(token->data);
	if (!cmd_arg)
		return (false);
	node = ft_lstnew(cmd_arg);
	if (!node)
		return (free(cmd_arg), false);
	ft_lstadd_back(&cmd_table->cmd_args, node);
	return (true);
}

bool	fill_assignment(t_token *token, t_cmd_table *cmd_table)
{
	char	*assignment;
	t_list	*node;

	assignment = ft_strdup(token->data);
	if (!assignment)
		return (false);
	node = ft_lstnew(assignment);
	if (!node)
		return (free(assignment), false);
	ft_lstadd_back(&cmd_table->assignment_list, node);
	return (true);
}

bool	handle_word_token(t_list **token_list, t_list_d **cmd_table_list)
{
	t_token		*token;
	t_cmd_table	*cmd_table;

	token = get_token_from_list(*token_list);
	cmd_table = get_last_simple_cmd_table(*cmd_table_list);
	cmd_table->type = C_SIMPLE_CMD;
	if (token->type == T_WORD)
	{
		if (fill_cmd_name(token, cmd_table))
			return (true);
		else if (fill_cmd_args(token, cmd_table))
			return (true);
	}
	else if (token->type == T_ASSIGNMENT_WORD)
	{
		if (fill_assignment(token, cmd_table))
			return (true);
	}
	return (false);
}
