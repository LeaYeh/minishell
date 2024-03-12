/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_table_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:02:02 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/23 04:06:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"

void	free_final_cmd_table(t_final_cmd_table **final_cmd_table, bool close_fd)
{
	if (!final_cmd_table || !*final_cmd_table)
		return ;
	free_array(&(*final_cmd_table)->env);
	free_array(&(*final_cmd_table)->simple_cmd);
	ft_free_and_null((void **)&(*final_cmd_table)->exec_path);
	free_array(&(*final_cmd_table)->assignment_array);
	if (close_fd)
	{
		safe_close(&(*final_cmd_table)->read_fd);
		safe_close(&(*final_cmd_table)->write_fd);
	}
	ft_free_and_null((void **)final_cmd_table);
}

bool	set_final_cmd_table(t_shell *shell, t_cmd_table *cmd_table)
{
	free_final_cmd_table(&shell->final_cmd_table, false);
	shell->final_cmd_table = (t_final_cmd_table *)ft_calloc(
			1, sizeof(t_final_cmd_table));
	if (!shell->final_cmd_table || \
		!setup_env(shell->final_cmd_table, shell->env_list) || \
		!setup_simple_cmd(shell, cmd_table->simple_cmd_list) || \
		!setup_exec_path(shell->final_cmd_table) || \
		!setup_assignment_array(
			shell->final_cmd_table, cmd_table->assignment_list))
		return (false);
	setup_fd(shell, shell->final_cmd_table);
	return (true);
}
