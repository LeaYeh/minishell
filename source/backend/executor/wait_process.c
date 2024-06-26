/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 14:30:49 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/04 22:49:27 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean.h"
#include "utils.h"

static int	handle_exit_status(int wstatus);
static void	print_signaled_exit_msg(int wstatus, int signo);

bool	wait_process(t_sh *shell, pid_t pid)
{
	int	wstatus;

	if (waitpid(pid, &wstatus, 0) == -1)
		return (false);
	shell->exit_code = handle_exit_status(wstatus);
	return (true);
}

void	wait_all_child_pid(t_sh *shell)
{
	t_list	*child_pid_node;
	bool	got_sigint;
	pid_t	pid;
	int		wstatus;

	got_sigint = false;
	child_pid_node = shell->child_pid_list;
	pid = (pid_t)(long)child_pid_node->content;
	if (wait_process(shell, pid) && shell->exit_code == TERM_BY_SIGNAL + SIGINT)
		got_sigint = true;
	child_pid_node = child_pid_node->next;
	while (child_pid_node)
	{
		pid = (pid_t)(long)child_pid_node->content;
		if (waitpid(pid, &wstatus, 0) != -1 && \
			WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
			got_sigint = true;
		child_pid_node = child_pid_node->next;
	}
	if (got_sigint)
		ft_printf("\n");
}

static int	handle_exit_status(int wstatus)
{
	int	signo;

	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
	{
		signo = WTERMSIG(wstatus);
		if (signo == SIGQUIT || signo == SIGSEGV)
			print_signaled_exit_msg(wstatus, signo);
		return (TERM_BY_SIGNAL + signo);
	}
	return (UNEXPECT_EXIT);
}

static void	print_signaled_exit_msg(int wstatus, int signo)
{
	char	*exit_msg;

	if (signo == SIGQUIT)
		exit_msg = "Quit";
	else if (signo == SIGSEGV)
		exit_msg = "Segmentation fault";
	else
		exit_msg = "";
	if (WCOREDUMP(wstatus))
		print_error("%s (core dumped)\n", exit_msg);
	else
		print_error("%s\n", exit_msg);
}
