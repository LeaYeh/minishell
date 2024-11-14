/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:32:12 by lyeh              #+#    #+#             */
/*   Updated: 2024/06/01 11:50:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include "clean.h"
#include "signals.h"

static void	iter_pipeline(t_sh *shell, t_list_d **cmd_table_node);
static bool	insert_child_pid_list(t_sh *shell, pid_t pid);
static void	exec_cmd_table(
				t_sh *shell,
				t_list_d **cmd_table_node,
				t_ct_typ cmd_table_type);
static void	handle_end_of_pipeline(t_sh *shell, t_list_d **cmd_table_node);

void	fork_pipeline(t_sh *shell, t_list_d **cmd_table_node)
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
		setup_signal(SIGINT, SIG_IGNORE);
		setup_signal(SIGTERM, SIG_STANDARD);
		shell->subshell_level += 1;
		handle_pipes_child(&shell->new_pipe, &shell->old_pipe);
		iter_pipeline(shell, cmd_table_node);
	}
	else
	{
		setup_signal(SIGINT, SIG_RECORD);
		move_past_pipeline(cmd_table_node);
		handle_end_of_pipeline(shell, cmd_table_node);
		shell->subshell_pid = -1;
		setup_signal(SIGINT, SIG_STANDARD);
	}
}

static void	iter_pipeline(t_sh *shell, t_list_d **cmd_table_node)
{
	t_ct_typ	cmd_table_type;

	cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
	while (true)
	{
		if (cmd_table_type == C_SUBSHELL_START || \
			cmd_table_type == C_SIMPLE_CMD)
			exec_cmd_table(shell, cmd_table_node, cmd_table_type);
		else if (cmd_table_type == C_PIPE)
			*cmd_table_node = (*cmd_table_node)->next;
		else
			break ;
		cmd_table_type = get_cmd_table_type_from_list(*cmd_table_node);
	}
	safe_close_all_pipes(shell);
	wait_all_child_pid(shell);
	clean_and_exit_shell(shell, shell->exit_code, NULL);
}

static void	exec_cmd_table(
				t_sh *shell,
				t_list_d **cmd_table_node,
				t_ct_typ cmd_table_type)
{
	if (need_pipe(*cmd_table_node) && !create_pipe(&shell->new_pipe))
		raise_error_to_all_subprocess(
			shell, TERM_BY_SIGNAL + SIGHUP, ERROR_CREATE_PIPE);
	if (cmd_table_type == C_SUBSHELL_START)
		fork_subshell(shell, cmd_table_node);
	else if (cmd_table_type == C_SIMPLE_CMD)
		fork_simple_cmd(shell, cmd_table_node);
	if (!insert_child_pid_list(shell, shell->subshell_pid))
		raise_error_to_own_subprocess(shell, MALLOC_ERROR, MALLOC_FMSG);
	handle_pipes_parent(&shell->new_pipe, &shell->old_pipe);
}

static bool	insert_child_pid_list(t_sh *shell, pid_t pid)
{
	return (ft_lstnew_front(&shell->child_pid_list, (void *)(long)pid));
}

static void	handle_end_of_pipeline(t_sh *shell, t_list_d **cmd_table_node)
{
	t_ct_typ	cmd_table_type;

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
			clean_and_exit_shell(shell, shell->exit_code, NULL);
		}
	}
}
