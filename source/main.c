/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:09:49 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/18 16:20:38 by ldulling         ###   ########.fr       */
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
				printf("\n"EXIT_STR);
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

	errno = SUCCESS;
	if (isatty(fileno(stdin)))
		shell->input_line = readline(PROMPT);
	else
	{
		line = get_next_line(fileno(stdin));
		if (line)
		{
			shell->input_line = ft_strtrim(line, "\n");
			free(line);
		}
	}
	if (errno != SUCCESS)
		return (false);
	add_history(shell->input_line);
	return (errno == SUCCESS);
}
