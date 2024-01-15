/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:30:49 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/14 19:44:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "clean.h"

int	handle_exit_status(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
	{
		if (WCOREDUMP(wstatus))
			printf("Quit (core dumped)\n");
		return (TERM_BY_SIGNAL + WTERMSIG(wstatus));
	}
	return (UNEXPECT_EXIT);
}

// if critical error, exit current process and propagate for whole shell
void	wait_process(t_shell *shell, int pid)
{
	if (waitpid(pid, &shell->exit_status, 0) == -1)
	{
		shell->exit_code = UNEXPECT_EXIT;
		return (perror(PROGRAM_NAME));
	}
	shell->exit_code = handle_exit_status(shell->exit_status);
	if (shell->exit_code == GENERAL_ERROR)
		ft_clean_and_exit_shell(shell, GENERAL_ERROR, NULL);
}
