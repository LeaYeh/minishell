/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:28:20 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/12 14:44:43 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

// TODO: Need to verify if the return value always be one of the operators
char	*get_error_token_data(t_list *token_list, t_list *parse_stack)
{
	char	*error_token_data;

	if (token_list)
		error_token_data = get_token_data_from_list(token_list);
	else
		error_token_data = get_ast_from_stack(parse_stack)->data;
	return (error_token_data);
}

void	report_syntax_error(t_parser_data *parser_data)
{
	ft_dprintf(STDERR_FILENO, ERROR_PARSER_SYNTAX,
		PROGRAM_NAME,
		get_error_token_data(
<<<<<<< HEAD
			parser_data->token_list,
			parser_data->parse_stack));
=======
			parser_data->token_list, parser_data->parse_stack));
>>>>>>> 269fb07 (refactor: Change parser interface to diff between parsing and general error)
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
<<<<<<< HEAD
		{
			free_parser_data(parser_data);
			ft_clean_and_exit_shell(shell, GENERAL_ERROR);
		}
		if (!pt_entry)
			return (report_syntax_error(parser_data), false);
		if (pt_entry->action == A_ACCEPT)
			return (free(pt_entry), true);
		if (!parse_step(parser_data, pt_entry))
		{
			free(pt_entry);
			free_parser_data(parser_data);
			ft_clean_and_exit_shell(shell, GENERAL_ERROR);
		}
		ft_free_and_null((void **)&pt_entry);
	}
=======
			ft_clean_and_exit_shell(shell, GENERAL_ERROR);
		if (!pt_entry)
			return (report_syntax_error(parser_data), false);
		if (pt_entry->action == A_ACCEPT)
			break ;
		if (!parse_step(parser_data, pt_entry))
		{
			free(pt_entry);
			ft_clean_and_exit_shell(shell, GENERAL_ERROR);
		}
		ft_free_and_null((void **)&pt_entry);
	}
	return (free(pt_entry), true);
>>>>>>> 269fb07 (refactor: Change parser interface to diff between parsing and general error)
}

t_ast	*extract_ast_from_parse_stack(t_list **parse_stack)
{
	t_ast	*ast;

	if (ft_lstsize(*parse_stack) != 2 || \
		get_ast_from_stack(*parse_stack)->type != T_END)
		return (NULL);
	drop_num_stack(parse_stack, 1, (void *)free_ast_node);
	ast = ft_lstpop_front_content(parse_stack);
	return (ast);
}

// TODO: dup the token_list in parse() or init_parse()?
// TODO: Need to refactor the code if AST is not necessary
bool	ft_parser(t_shell *shell)
{
	t_parser_data	parser_data;

	if (!init_parser_data(&parser_data, shell->token_list))
		ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	if (!parse(shell, &parser_data))
<<<<<<< HEAD
		return (free_parser_data(&parser_data), false);
	free_parser_data(&parser_data);
	printf("ACCEPT\n");
	shell->cmd_table_list = build_cmd_table_list(shell->token_list);
=======
		return (free_parser_data(&parser_data), true);
	printf("ACCEPT\n");
	shell->cmd_table_list = build_cmd_table_list(shell->token_list);
	free_parser_data(&parser_data);
	ft_lstclear(&shell->token_list, (void *)free_token_node);
>>>>>>> 269fb07 (refactor: Change parser interface to diff between parsing and general error)
	if (!shell->cmd_table_list)
		ft_clean_and_exit_shell(shell, GENERAL_ERROR);
	ft_lstclear(&shell->token_list, (void *)free_token_node);
	return (true);
}
