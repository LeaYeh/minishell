/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:02:15 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/08 12:27:27 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean.h"
#include "executor.h"
#include "utils.h"

static void	clean_shell(t_sh *shell);
static void	remove_heredoc_files(t_ct *cmd_table);
static void	close_std_io(void);

void	clean_and_exit_shell(t_sh *shell, int exit_code, char *msg)
{
	if (msg)
		print_error("%s: %s\n", PROGRAM_NAME, msg);
	clean_shell(shell);
	safe_close_all_pipes(shell);
	free_get_next_line();
	close_std_io();
	exit(exit_code);
}

void	reset_submodule_variable(t_sh *shell)
{
	shell->subshell_level = 0;
	shell->subshell_pid = -1;
	shell->signal_record = 0;
	ft_lstclear(&shell->child_pid_list, NULL);
	ft_lstclear(&shell->token_list, (void *)free_token);
	ft_lstiter_d(shell->cmd_table_list, (void *)remove_heredoc_files);
	ft_lstclear_d(&shell->cmd_table_list, (void *)free_cmd_table);
	ft_free_and_null((void **)&shell->input_line);
	free_final_cmd_table(&shell->final_cmd_table);
}

static void	clean_shell(t_sh *shell)
{
	ft_free_and_null((void **)&shell->input_line);
	ft_lstclear(&shell->child_pid_list, NULL);
	ft_lstclear(&shell->env_list, (void *)free_env_node);
	ft_lstclear(&shell->token_list, (void *)free_token);
	if (shell->subshell_level == 0)
		ft_lstiter_d(shell->cmd_table_list, (void *)remove_heredoc_files);
	ft_lstclear_d(&shell->cmd_table_list, (void *)free_cmd_table);
	free_final_cmd_table(&shell->final_cmd_table);
	ft_free_and_null(&shell->builtin_allocation);
	rl_clear_history();
}

static void	remove_heredoc_files(t_ct *cmd_table)
{
	t_list		*io_red_list;
	t_io_red	*io_red;

	if (!cmd_table)
		return ;
	io_red_list = cmd_table->io_red_list;
	while (io_red_list)
	{
		io_red = io_red_list->content;
		if (io_red->type == T_HERE_DOC)
			remove_file(io_red->filename);
		io_red_list = io_red_list->next;
	}
}

static void	close_std_io(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
