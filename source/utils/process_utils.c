/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:30:49 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/25 16:25:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "clean.h"

int	handle_exit_status(int wstatus)
{
	int	signo;

	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
	{
		signo = WTERMSIG(wstatus);
		if (signo == SIGQUIT)
			ft_dprintf(STDERR_FILENO, "Quit");
		else if (signo == SIGSEGV)
			ft_dprintf(STDERR_FILENO, "Segmentation fault");
		if (WCOREDUMP(wstatus))
			ft_dprintf(STDERR_FILENO, " (core dumped)");
		ft_dprintf(STDERR_FILENO, "\n");
		return (TERM_BY_SIGNAL + signo);
	}
	return (UNEXPECT_EXIT);
}

void	wait_process(t_shell *shell, pid_t pid)
{
	waitpid(pid, &shell->exit_status, 0);
	shell->exit_code = handle_exit_status(shell->exit_status);
}
