/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:10:43 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/09 20:37:25 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"

int	handle_builtin(t_shell *shell, t_list_d **cmd_table_node)
{
	t_cmd_table	*cmd_table;

	(void)shell;
	cmd_table = (*cmd_table_node)->content;
	if (!cmd_table->cmd_name)
		return (GENERAL_ERROR);
	shell->subshell_pid = -1;
	*cmd_table_node = (*cmd_table_node)->next;
	if (ft_strcmp(cmd_table->cmd_name, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd_table->cmd_name, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd_table->cmd_name, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd_table->cmd_name, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd_table->cmd_name, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd_table->cmd_name, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd_table->cmd_name, "exit") == 0)
		return (0);
	return (GENERAL_ERROR);
}
