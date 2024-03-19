/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:28:20 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 18:08:54 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean.h"
#include "parser.h"
#include "utils.h"

bool	parse_step(t_parser_data *parser_data, t_pt_node *pt_entry)
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
					get_token_from_stack(parser_data->parse_stack)->type)))
			return (false);
	}
	return (true);
}

char	*get_error_token_data(t_list *token_list, t_list *parse_stack)
{
	char	*error_token_data;

	if (token_list)
		error_token_data = get_token_data_from_list(token_list);
	else
		error_token_data = get_ast_from_stack(parse_stack)->data;
	return (error_token_data);
}

void	report_syntax_error(t_shell *shell, t_parser_data *parser_data)
{
	char	*error_token;

	error_token = get_error_token_data(
			parser_data->token_list, parser_data->parse_stack);
	if (!error_token)
		error_token = "newline";
	shell->exit_code = SYNTAX_ERROR;
	ft_dprintf(STDERR_FILENO, ERROR_PARSER_SYNTAX, PROGRAM_NAME, error_token);
}

bool	parse(t_shell *shell, t_parser_data *parser_data)
{
	t_pt_node	*pt_entry;

	pt_entry = NULL;
	while (true)
	{
		if (!set_next_pt_entry(&pt_entry,
				get_state_from_stack(parser_data->state_stack),
				get_token_type_from_list(parser_data->token_list),
				A_SHIFT | A_REDUCE | A_ACCEPT))
			(free_parser_data(parser_data),
				ft_clean_and_exit_shell(
					shell, PREPROCESS_ERROR, "parser malloc failed"));
		if (!pt_entry)
			return (report_syntax_error(shell, parser_data), false);
		if (pt_entry->action == A_ACCEPT)
			return (free(pt_entry), true);
		if (!parse_step(parser_data, pt_entry))
		{
			free(pt_entry);
			free_parser_data(parser_data);
			ft_clean_and_exit_shell(
				shell, PREPROCESS_ERROR, "parser malloc failed");
		}
		ft_free_and_null((void **)&pt_entry);
	}
}

bool	ft_parser(t_shell *shell)
{
	t_parser_data	parser_data;

	if (!init_parser_data(&parser_data, shell->token_list))
		ft_clean_and_exit_shell(
			shell, PREPROCESS_ERROR, "parser malloc failed");
	if (!parse(shell, &parser_data))
		return (free_parser_data(&parser_data), false);
	free_parser_data(&parser_data);
	shell->cmd_table_list = build_cmd_table_list(shell->token_list);
	if (!shell->cmd_table_list)
		ft_clean_and_exit_shell(
			shell, PREPROCESS_ERROR, "build cmd table malloc failed");
	ft_lstclear(&shell->token_list, (void *)free_token_node);
	return (true);
}
