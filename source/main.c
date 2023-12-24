/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:09:49 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/26 18:31:44 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean.h"
#include "lexer.h"
#include "parser.h"
#include "debug.h"
#include "tests.h"
#include "utils.h"

bool	ft_read_input(t_shell *shell);

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	((void)argc, (void)argv);
	if (!ft_init_shell(&shell, env))
		return (EXIT_FAILED);
	// init signal handler
	// return correct exit code
	while (true)
	{
		if (!ft_read_input(&shell))
			return (ft_clean_shell(&shell), EXIT_FAILED);
		if (!shell.input_line || ft_strlen(shell.input_line) == 0 \
			|| shell.input_line[0] == '\n')
			continue ;
		if (!ft_lexer(&shell))
			return (ft_clean_shell(&shell), EXIT_FAILED);
		if (!ft_parse(&shell))
			return (ft_clean_shell(&shell), EXIT_FAILED);

		// Free ast after executor
		free_ast_node(shell.ast);
		shell.ast = NULL;
		// ft_clean_shell(&shell);
		// do executor
	}
	return (EXIT_SUCCESS);
}

bool	ft_read_input(t_shell *shell)
{
	char	*line;

	ft_free_and_null((void **) &shell->input_line);
	line = readline(PROMPT);
	if (!line)
		return (false);
	shell->input_line = line;
	add_history(shell->input_line);
	return (true);
}
