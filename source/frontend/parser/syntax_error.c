/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:20:32 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 17:22:15 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static char	*get_error_token_data(t_list *token_list, t_list *parse_stack);

void	report_syntax_error(t_sh *shell, t_prs_data *parser_data)
{
	char	*error_token;

	error_token = get_error_token_data(
			parser_data->token_list, parser_data->parse_stack);
	if (!error_token)
		error_token = "newline";
	shell->exit_code = SYNTAX_ERROR;
	ft_dprintf(STDERR_FILENO, ERROR_PARSER_SYNTAX, PROGRAM_NAME, error_token);
}

static char	*get_error_token_data(t_list *token_list, t_list *parse_stack)
{
	char	*error_token_data;

	if (token_list)
		error_token_data = get_token_data_from_list(token_list);
	else
		error_token_data = get_ast_from_stack(parse_stack)->data;
	return (error_token_data);
}
