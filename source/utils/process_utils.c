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

static void	print_exit_msg(int wstatus, int signo)
{
	if (signo == SIGQUIT)
		ft_dprintf(STDERR_FILENO, "Quit");
	else if (signo == SIGSEGV)
		ft_dprintf(STDERR_FILENO, "Segmentation fault");
	if (WCOREDUMP(wstatus))
		ft_dprintf(STDERR_FILENO, " (core dumped)");
	ft_dprintf(STDERR_FILENO, "\n");
}

int	handle_exit_status(int wstatus)
{
	int	signo;

	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
	{
		signo = WTERMSIG(wstatus);
		if (signo == SIGQUIT || signo == SIGSEGV)
			print_exit_msg(wstatus, signo);
		return (TERM_BY_SIGNAL + signo);
	}
	return (UNEXPECT_EXIT);
}

void	wait_process(t_shell *shell, pid_t pid)
{
	int	wstatus;

	if (waitpid(pid, &wstatus, 0) != -1)
		shell->exit_code = handle_exit_status(wstatus);
}
