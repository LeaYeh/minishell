/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_table_operation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:27:22 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 17:11:05 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "clean.h"

static bool			match_rule(
						int token_type,
						t_prs_act action_mask,
						int row_index,
						const int parsing_table[PT_ROW_NUM][PT_COL_NUM]);
static t_pt_node	*init_pt_node(
						const int pt_row[PT_ROW_NUM]);

bool	set_next_pt_entry(
	t_pt_node **pt_entry,
	int state,
	int token_type,
	t_prs_act action_mask)
{
	const int	parsing_table[PT_ROW_NUM][PT_COL_NUM] = PARSING_TABLE;
	int			i;

	i = 0;
	while (i < PT_ROW_NUM)
	{
		if (parsing_table[i][PT_COL_STATE] == state)
		{
			if (match_rule(token_type, action_mask, i, parsing_table))
				break ;
		}
		i++;
	}
	if (i == PT_ROW_NUM)
		return (true);
	*pt_entry = init_pt_node(parsing_table[i]);
	if (!*pt_entry)
		return (false);
	return (true);
}

static bool	match_rule(
	int token_type,
	t_prs_act action_mask,
	int row_index,
	const int parsing_table[PT_ROW_NUM][PT_COL_NUM])
{
	if ((action_mask & A_ACCEPT) == A_ACCEPT && \
		parsing_table[row_index][PT_COL_ACTION] == A_ACCEPT)
		return (true);
	else if ((action_mask & A_SHIFT) && \
		parsing_table[row_index][PT_COL_ACTION] == A_SHIFT && \
		parsing_table[row_index][PT_COL_TOKEN_TYPE] == token_type)
		return (true);
	else if ((action_mask & A_REDUCE) && \
		parsing_table[row_index][PT_COL_ACTION] == A_REDUCE)
		return (true);
	else if ((action_mask & A_GOTO) && \
		parsing_table[row_index][PT_COL_ACTION] == A_GOTO && \
		parsing_table[row_index][PT_COL_TOKEN_TYPE] == token_type)
		return (true);
	return (false);
}

static t_pt_node	*init_pt_node(
	const int pt_row[PT_ROW_NUM])
{
	t_pt_node	*pt_node;

	pt_node = (t_pt_node *)malloc(sizeof(t_pt_node));
	if (!pt_node)
		return (NULL);
	pt_node->state = pt_row[PT_COL_STATE];
	pt_node->token_type = pt_row[PT_COL_TOKEN_TYPE];
	pt_node->action = pt_row[PT_COL_ACTION];
	pt_node->next_state = pt_row[PT_COL_NEXT_STATE];
	pt_node->num_reduced = pt_row[PT_COL_NUM_REDUCED];
	return (pt_node);
}
