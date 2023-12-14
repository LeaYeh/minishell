/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:09:49 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/14 22:32:56 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "clean.h"
#include "debug.h"

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
		if (ft_strlen(shell.input_line) == 1 && shell.input_line[0] == '\n')
			continue ;
		// do lexer -> tokens
		// do parser -> ast
		// do executor
	}
	return (EXIT_SUCCESS);
}

bool	ft_read_input(t_shell *shell)
{
	char	*line;

	if (shell->input_line != NULL)
	{
		free(shell->input_line);
		shell->input_line = NULL;
	}
	line = readline(PROMPT);
	if (!line)
		return (false);
	shell->input_line = line;
	add_history(shell->input_line);
	return (true);
}
