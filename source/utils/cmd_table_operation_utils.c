/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_operation_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:30:35 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/18 03:08:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_cmd_table(t_ct *cmd_table)
{
	if (!cmd_table)
		return ;
	ft_lstclear(&cmd_table->simple_cmd_list, free);
	ft_lstclear(&cmd_table->assignment_list, free);
	ft_lstclear(&cmd_table->io_red_list, (void *)free_io_red);
	free(cmd_table);
}

t_ct	*init_cmd_table(void)
{
	t_ct	*cmd_table;

	cmd_table = (t_ct *)malloc(sizeof(t_ct));
	if (!cmd_table)
		return (NULL);
	cmd_table->id = 0;
	cmd_table->type = C_SIMPLE_CMD;
	cmd_table->subshell_level = 0;
	cmd_table->read_fd = -1;
	cmd_table->write_fd = -1;
	cmd_table->assignment_list = NULL;
	cmd_table->simple_cmd_list = NULL;
	cmd_table->io_red_list = NULL;
	return (cmd_table);
}
