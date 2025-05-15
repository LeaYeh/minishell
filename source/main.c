/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:09:49 by lyeh              #+#    #+#             */
/*   Updated: 2024/05/30 23:54:25 by ldulling         ###   ########.fr       */
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

int	main(void)
{
	t_sh	shell;

	if (!DEFINITIONS_OK || !init_shell(&shell))
		clean_and_exit_shell(&shell, MALLOC_ERROR, "init shell failed");
	print_welcome_msg(&shell);
	while (true)
	{
		if (!read_input(&shell.input_line, &shell, PROMPT, true))
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
