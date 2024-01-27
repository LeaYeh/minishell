/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:12 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/25 16:49:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "clean.h"
#include "signals.h"

// iter wait from the last child pid in the list
void	wait_all_child_pid(t_shell *shell)
{
	t_list	*child_pid_node;
	int		i;
	pid_t	pid;
	int		status;

	child_pid_node = shell->child_pid_list;
	i = 0;
	while (child_pid_node)
	{
		pid = *(pid_t *)child_pid_node->content;
		if (i == 0)
			wait_process(shell, pid);
		waitpid(pid, &status, 0);
		i++;
		child_pid_node = child_pid_node->next;
	}
	if (shell->subshell_level <= 1 && shell->exit_code == 130)
		printf("\n");
}

bool	insert_child_pid_list(t_shell *shell, pid_t pid)
{
	pid_t	*pid_ptr;

	pid_ptr = malloc(sizeof(pid_t));
	if (!pid_ptr)
		return (false);
	*pid_ptr = pid;
	if (!ft_lstnew_front(&shell->child_pid_list, pid_ptr))
	{
		free(pid_ptr);
		return (false);
	}
	return (true);
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
			// do T1, handle_pipe
			if (need_pipe(*cmd_table_node) && !create_pipe(&shell->new_pipe))
				ft_clean_and_exit_shell(shell, SUBSHELL_ERROR, "pipe failed");
			if (cmd_table_type == C_SUBSHELL_START)
				handle_subshell(shell, cmd_table_node);
			else if (cmd_table_type == C_SIMPLE_CMD)
				handle_simple_cmd(shell, cmd_table_node);
			// do T2.1
			if (!insert_child_pid_list(shell, shell->subshell_pid))
				ft_clean_and_exit_shell(shell, SUBSHELL_ERROR, "malloc failed");
			handle_pipes_parent(&shell->new_pipe, &shell->old_pipe);
		}
		cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
	}
	// do T2.2
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
		// do T2.2
		safe_close_all_pipes(shell);
		wait_process(shell, shell->subshell_pid);
		if (shell->subshell_level != 0)
			ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
	}
}

// handle_pipeline = handle_one_pipeline
void	handle_pipeline(t_shell *shell, t_list_d **cmd_table_node)
{
	setup_signal(shell, SIGINT, SIG_IGNORE);
	shell->subshell_pid = fork();
	if (shell->subshell_pid == -1)
		ft_clean_and_exit_shell(
			shell, SUBSHELL_ERROR, "handle_pipeline, fork failed");
	else if (shell->subshell_pid == 0)
	{
		shell->subshell_level += 1;
		// do T0
		handle_pipes_child(&shell->new_pipe, &shell->old_pipe);
		exec_pipeline(shell, cmd_table_node);
	}
	else
	{
		move_past_pipeline(cmd_table_node);
		handle_end_of_pipeline(shell, cmd_table_node);
		setup_signal(shell, SIGINT, SIG_STD);
	}
}
