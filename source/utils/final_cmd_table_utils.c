/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_table_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:02:02 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/04 22:30:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"

int	set_final_cmd_table(t_sh *shell, t_ct *cmd_table)
{
	int	ret;

	shell->final_cmd_table = (t_fct *)ft_calloc(1, sizeof(t_fct));
	if (!shell->final_cmd_table)
		return (MALLOC_ERROR);
	ret = setup_simple_cmd(shell, cmd_table->simple_cmd_list);
	if (ret == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (!setup_env(shell->final_cmd_table, shell->env_list) || \
		!setup_exec_path(shell, shell->final_cmd_table) || \
		!setup_assignment_array(
			shell->final_cmd_table, cmd_table->assignment_list))
		return (MALLOC_ERROR);
	setup_fd(shell, shell->final_cmd_table);
	return (ret);
}

void	free_final_cmd_table(t_fct **final_cmd_table)
{
	if (!final_cmd_table || !*final_cmd_table)
		return ;
	free_array(&(*final_cmd_table)->env);
	free_array(&(*final_cmd_table)->simple_cmd);
	ft_free_and_null((void **)&(*final_cmd_table)->exec_path);
	free_array(&(*final_cmd_table)->assignment_array);
	safe_close(&(*final_cmd_table)->read_fd);
	safe_close(&(*final_cmd_table)->write_fd);
	ft_free_and_null((void **)final_cmd_table);
}
