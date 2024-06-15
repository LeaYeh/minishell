/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:07:04 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/18 01:26:58 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static bool	fill_simple_cmd(t_tok *token, t_ct *cmd_table);
static bool	fill_assignment(t_tok *token, t_ct *cmd_table);

bool	handle_word_token(t_list **token_list, t_list_d **cmd_table_list)
{
	t_tok	*token;
	t_ct	*cmd_table;

	token = get_token_from_list(*token_list);
	cmd_table = get_last_simple_cmd_table(*cmd_table_list);
	cmd_table->type = C_SIMPLE_CMD;
	if (token->type == T_WORD)
		return (fill_simple_cmd(token, cmd_table));
	else if (token->type == T_ASSIGNMENT_WORD)
		return (fill_assignment(token, cmd_table));
	return (false);
}

static bool	fill_simple_cmd(t_tok *token, t_ct *cmd_table)
{
	char	*cmd_arg;

	cmd_arg = ft_strdup(token->data);
	if (!cmd_arg)
		return (false);
	if (!ft_lstnew_back(&cmd_table->simple_cmd_list, cmd_arg))
		return (free(cmd_arg), false);
	return (true);
}

static bool	fill_assignment(t_tok *token, t_ct *cmd_table)
{
	char	*assignment;

	assignment = ft_strdup(token->data);
	if (!assignment || !ft_lstnew_back(&cmd_table->assignment_list, assignment))
		return (free(assignment), false);
	return (true);
}
