/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:12 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/19 15:19:03 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "clean.h"
#include "signals.h"

void	wait_all_child_pid(t_shell *shell)
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
		printf("\n");
}

bool	insert_child_pid_list(t_shell *shell, pid_t pid)
{
	return (ft_lstnew_front(&shell->child_pid_list, (void *)(long)pid));
}

void	exec_pipeline(t_shell *shell, t_list_d **cmd_table_node)
{
	int	cmd_table_type;

	cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
	while (cmd_table_type == C_PIPE || \
		cmd_table_type == C_SUBSHELL_START || cmd_table_type == C_SIMPLE_CMD)
	{
		if (cmd_table_type == C_PIPE)
			*cmd_table_node = (*cmd_table_node)->next;
		else
		{
			if (need_pipe(*cmd_table_node) && !create_pipe(&shell->new_pipe))
				raise_error_to_all_subprocess(
					shell, TERM_BY_SIGNAL + SIGHUP, ERROR_CREATE_PIPE);
			if (cmd_table_type == C_SUBSHELL_START)
				fork_subshell(shell, cmd_table_node);
			else if (cmd_table_type == C_SIMPLE_CMD)
				fork_simple_cmd(shell, cmd_table_node);
			if (!insert_child_pid_list(shell, shell->subshell_pid))
				raise_error_to_own_subprocess(
					shell, MALLOC_ERROR, "malloc failed");
			handle_pipes_parent(&shell->new_pipe, &shell->old_pipe);
		}
		cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
	}
	safe_close_all_pipes(shell);
	wait_all_child_pid(shell);
	ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
}

void	handle_end_of_pipeline(t_shell *shell, t_list_d **cmd_table_node)
{
	int	cmd_table_type;

	cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
	if (is_control_op_cmd_table(cmd_table_type))
		handle_control_op(shell, cmd_table_node);
	else
	{
		safe_close_all_pipes(shell);
		wait_process(shell, shell->subshell_pid);
		if (shell->subshell_level != 0)
		{
			if (shell->signal_record != 0)
				shell->exit_code = TERM_BY_SIGNAL + shell->signal_record;
			ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
		}
	}
}

void	fork_pipeline(t_shell *shell, t_list_d **cmd_table_node)
{
	shell->subshell_pid = fork();
	if (shell->subshell_pid == -1)
	{
		raise_error_to_all_subprocess(
			shell, FORK_ERROR, "pipeline fork failed");
		*cmd_table_node = NULL;
	}
	else if (shell->subshell_pid == 0)
	{
		setup_signal(shell, SIGINT, SIG_IGNORE);
		setup_signal(shell, SIGTERM, SIG_STANDARD);
		shell->subshell_level += 1;
		handle_pipes_child(&shell->new_pipe, &shell->old_pipe);
		exec_pipeline(shell, cmd_table_node);
	}
	else
	{
		setup_signal(shell, SIGINT, SIG_RECORD);
		move_past_pipeline(cmd_table_node);
		handle_end_of_pipeline(shell, cmd_table_node);
		shell->subshell_pid = -1;
		setup_signal(shell, SIGINT, SIG_STANDARD);
	}
}
