/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:09:49 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/19 17:06:47 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean.h"
#include "init.h"
#include "builtins.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "utils.h"
#include "signals.h"

bool	read_input(char **line,
			char *prompt, bool add_to_history, bool is_interactive);

int	main(void)
{
	t_shell	shell;

	if (!DEFINITIONS_OK || !init_shell(&shell))
		raise_error_and_escape(&shell, "init shell failed");
	while (true)
	{
		if (!read_input(&shell.input_line, PROMPT, true, shell.is_interactive))
			continue ;
		if (!shell.input_line)
			exec_exit(&shell, NULL);
		if (!lexer(&shell) || !parser(&shell))
		{
			reset_submodule_variable(&shell);
			continue ;
		}
		if (shell.cmd_table_list)
			executor(&shell);
		reset_submodule_variable(&shell);
	}
	return (EXIT_SUCCESS);
}

bool	read_input(
	char **line, char *prompt, bool add_to_history, bool is_interactive)
{
	char	*tmp;

	errno = SUCCESS;
	if (is_interactive)
		*line = readline(prompt);
	else
	{
		tmp = get_next_line(STDIN_FILENO);
		if (errno != SUCCESS)
			return (false);
		if (tmp)
		{
			*line = ft_strtrim(tmp, "\n");
			free(tmp);
		}
	}
	if (errno == EINTR)
		errno = SUCCESS;
	else if (errno != SUCCESS)
		return (false);
	if (add_to_history && *line && **line)
		add_history(*line);
	return (errno == SUCCESS);
}
