/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:09:49 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/06 20:06:59 by ldulling         ###   ########.fr       */
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

bool	ft_read_input(t_shell *shell);

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	((void)argc, (void)argv);
	if (!ft_init_shell(&shell, env))
		return (GENERAL_ERROR);
	// init signal handler
	// return correct exit code
	while (true)
	{
		if (!ft_read_input(&shell))
			ft_clean_and_exit_shell(&shell, EXIT_SUCCESS);
		if (!shell.input_line || ft_strlen(shell.input_line) == 0 \
			|| shell.input_line[0] == '\n')
			continue ;
		if (!ft_lexer(&shell) || !ft_parser(&shell))
			ft_clean_and_exit_shell(&shell, GENERAL_ERROR);
		print_cmd_table_list(shell.cmd_table_list);
		if (!print_expanded_cmd_table_list(&shell))
			return (ft_clean_shell(&shell), 42);
		if (!ft_execute(&shell))
			return (ft_clean_shell(&shell), GENERAL_ERROR);
		ft_lstclear_d(&shell.cmd_table_list, (void *)free_cmd_table);
		ft_clean_shell(&shell);
	}
	return (EXIT_SUCCESS);
}

bool	ft_read_input(t_shell *shell)
{
	char	*line;

	ft_free_and_null((void **)&shell->input_line);
	line = readline(PROMPT);
	if (!line)
		return (false);
	shell->input_line = line;
	add_history(shell->input_line);
	return (true);
}
