/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:28:20 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/08 18:04:43 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean.h"
#include "parser.h"
#include "utils.h"

static bool	parse_step(t_prs_data *parser_data, t_pt_node *pt_entry);
static bool	parse(t_sh *shell, t_prs_data *parser_data);

bool	parser(t_sh *shell)
{
	t_prs_data	parser_data;

	if (!init_parser_data(&parser_data, shell->token_list))
		clean_and_exit_shell(shell, PREPROCESS_ERROR, "parser malloc failed");
	if (!parse(shell, &parser_data))
		return (free_parser_data(&parser_data), false);
	free_parser_data(&parser_data);
	shell->cmd_table_list = build_cmd_table_list(shell->token_list);
	if (!shell->cmd_table_list)
		clean_and_exit_shell(
			shell, PREPROCESS_ERROR, "build cmd table malloc failed");
	ft_lstclear(&shell->token_list, (void *)free_token);
	return (true);
}

static bool	parse(t_sh *shell, t_prs_data *parser_data)
{
	t_pt_node	*pt_entry;

	pt_entry = NULL;
	while (true)
	{
		if (!set_next_pt_entry(&pt_entry,
				get_state_from_stack(parser_data->state_stack),
				(t_prs_elem)get_token_type_from_list(parser_data->token_list),
				A_SHIFT | A_REDUCE | A_ACCEPT))
			(free_parser_data(parser_data),
				clean_and_exit_shell(
					shell, PREPROCESS_ERROR, "parser malloc failed"));
		if (!pt_entry)
			return (report_syntax_error(shell, parser_data), false);
		if (pt_entry->action == A_ACCEPT)
			return (free(pt_entry), true);
		if (!parse_step(parser_data, pt_entry))
		{
			free(pt_entry);
			free_parser_data(parser_data);
			clean_and_exit_shell(
				shell, PREPROCESS_ERROR, "parser malloc failed");
		}
		ft_free_and_null((void **)&pt_entry);
	}
}

static bool	parse_step(t_prs_data *parser_data, t_pt_node *pt_entry)
{
	if (pt_entry->action == A_SHIFT)
	{
		if (!parse_shift(ft_lstpop_front_content(&parser_data->token_list),
				&parser_data->state_stack,
				&parser_data->parse_stack, pt_entry->next_state))
			return (false);
	}
	else if (pt_entry->action == A_REDUCE)
	{
		if (!(parse_reduce(&parser_data->state_stack,
					&parser_data->parse_stack, pt_entry) && \
			parse_goto(&parser_data->state_stack,
					(t_prs_elem)get_token_from_stack(
						parser_data->parse_stack)->type)))
			return (false);
	}
	return (true);
}
