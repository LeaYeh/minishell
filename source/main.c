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

#include "minishell.h"
#include "clean.h"
#include "init.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "debug.h"
#include "tests.h"
#include "utils.h"
#include "signals.h"

bool	ft_read_input(t_shell *shell);

// If general error occurs, exit entire shell
// if syntax error occurs, continue to next input
int	main(void)
{
	t_shell	shell;

	if (!DEFINITIONS_OK || !init_shell(&shell))
		raise_error_and_escape(&shell, "init shell failed");
	while (true)
	{
		if (!ft_read_input(&shell))
			continue ;
		if (!shell.input_line)
		{
			if (!TEST_MODE)
				printf(EXIT_MSG);
			ft_clean_and_exit_shell(&shell, shell.exit_code, NULL);
		}
		if (!ft_lexer(&shell) || !ft_parser(&shell))
		{
			reset_submodule_variable(&shell);
			continue ;
		}
		if (shell.cmd_table_list)
			ft_executor(&shell);
		reset_submodule_variable(&shell);
	}
	return (EXIT_SUCCESS);
}

bool	ft_read_input(t_shell *shell)
{
	char	*line;

	char	term_buffer[2048];
	char	*term_type = getenv("TERM");
	char	*newline;

	tgetent(term_buffer, term_type);
	newline = tgetstr("nw", NULL);
	// tputs(newline, 1, putchar);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();

	errno = SUCCESS;
	if (isatty(STDIN_FILENO))
		shell->input_line = readline(PROMPT);
	else
	{
		errno = SUCCESS;
		line = get_next_line(STDIN_FILENO);
		if (errno != SUCCESS)
			return (false);
		if (line)
		{
			shell->input_line = ft_strtrim(line, "\n");
			free(line);
		}
	}
	if (errno == EINTR)
		errno = SUCCESS;
	else if (errno != SUCCESS)
		return (false);
	if (shell->input_line && *shell->input_line)
		add_history(shell->input_line);
	return (errno == SUCCESS);
}
