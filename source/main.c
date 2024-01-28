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
int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	((void)argc, (void)argv);
	// handle ctrl-C and ctrl-D and ignore ctrl-/
	if (!ft_init_shell(&shell, env))
		ft_clean_and_exit_shell(&shell, PREPROCESS_ERROR, "init shell failed");
	while (true)
	{
		if (!ft_read_input(&shell))
		{
			printf("\nexit\n");
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

	line = readline(PROMPT);
	if (!line)
		return (false);
	shell->input_line = line;
	add_history(shell->input_line);
	return (true);
}
