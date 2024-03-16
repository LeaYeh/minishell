/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:04:52 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/24 02:38:15 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "heredoc.h"
#include "clean.h"
#include "utils.h"
#include "debug.h"
#include "signals.h"

int	set_expanded_cmd_name(
	char **cmd_name, t_shell *shell, t_list *simple_cmd_list)
{
	t_list	*expanded_list;
	int		ret;

	expanded_list = NULL;
	ret = expand_list(shell, simple_cmd_list, &expanded_list, \
			E_EXPAND | E_SPLIT_WORDS | E_RM_QUOTES);
	*cmd_name = ft_lstpop_front_content(&expanded_list);
	ft_lstclear(&expanded_list, free);
	return (ret);
}

void	handle_expansion_error(
	t_shell *shell, t_list_d **cmd_table_node, int ret)
{
	if (ret == MALLOC_ERROR)
	{
		raise_error_to_own_subprocess(shell, MALLOC_ERROR, "malloc failed");
		move_past_pipeline(cmd_table_node);
	}
	else
	{
		shell->exit_code = ret;
		if (shell->subshell_level != 0)
			ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
		*cmd_table_node = NULL;
	}
}

void	handle_simple_cmd(t_shell *shell, t_list_d **cmd_table_node)
{
	char		*cmd_name;
	t_cmd_table	*cmd_table;
	int			ret;

	cmd_table = (*cmd_table_node)->content;
	ret = set_expanded_cmd_name(&cmd_name, shell, cmd_table->simple_cmd_list);
	if (ret != SUCCESS)
		return (free(cmd_name),
			handle_expansion_error(shell, cmd_table_node, ret));
	if (is_builtin(cmd_name))
	{
		free(cmd_name);
		if (set_final_cmd_table(shell, cmd_table) != SUCCESS)
			return (handle_expansion_error(
					shell, cmd_table_node, MALLOC_ERROR));
		handle_builtin(shell, cmd_table_node);
	}
	else
	{
		free(cmd_name);
		fork_pipeline(shell, cmd_table_node);
	}
}

void	handle_cmd_execution(t_shell *shell, t_list_d **cmd_table_node)
{
	if (is_scmd_in_pipeline(*cmd_table_node))
		fork_pipeline(shell, cmd_table_node);
	else
		handle_simple_cmd(shell, cmd_table_node);
}

void	handle_process(t_shell *shell, t_list_d *cmd_table_node)
{
	t_cmd_table	*cmd_table;

	while (cmd_table_node)
	{
		cmd_table = cmd_table_node->content;
		if (cmd_table->type == C_SUBSHELL_END)
			ft_clean_and_exit_shell(shell, shell->exit_code, NULL);
		else if (is_control_op_cmd_table(cmd_table->type))
			handle_control_op(shell, &cmd_table_node);
		else if (cmd_table->type == C_SIMPLE_CMD)
			handle_cmd_execution(shell, &cmd_table_node);
		else if (cmd_table->type == C_SUBSHELL_START)
			fork_pipeline(shell, &cmd_table_node);
		else
			raise_error_and_escape(shell, "unexpected unknown command type");
	}
}

// TODO: activate signal listener in the child process
void	ft_executor(t_shell *shell)
{
	int	heredoc_status;

	setup_signal(shell, SIGINT, SIG_HEREDOC);
	heredoc_status = ft_heredoc(shell);
	setup_signal(shell, SIGINT, SIG_STANDARD);
	if (heredoc_status == HEREDOC_ERROR)
		ft_clean_and_exit_shell(shell, MALLOC_ERROR, "heredoc malloc/fd error");
	else if (heredoc_status == HEREDOC_ABORT)
		return ;
	handle_process(shell, shell->cmd_table_list);
}
