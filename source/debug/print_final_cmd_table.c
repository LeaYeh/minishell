/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_final_cmd_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:17:36 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/18 03:21:43 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

static void	print_simple_cmd_array(char *simple_cmd[]);
static void	print_assignment_array(char *assignment_array[]);

void	print_final_cmd_table(t_fct *final_cmd_table)
{
	ft_printf("\n\n========= final cmd table =========\n");
	print_simple_cmd_array(final_cmd_table->simple_cmd);
	ft_printf("exec_path: %s\n", final_cmd_table->exec_path);
	ft_printf("read_fd: %d\n", final_cmd_table->read_fd);
	ft_printf("write_fd: %d\n", final_cmd_table->write_fd);
	print_assignment_array(final_cmd_table->assignment_array);
	ft_printf("===================================\n\n");
}

static void	print_simple_cmd_array(char *simple_cmd[])
{
	int	i;

	i = 0;
	ft_printf("simple_cmd:       ");
	while (simple_cmd && simple_cmd[i])
	{
		ft_printf("%s -> ", simple_cmd[i]);
		i++;
	}
	ft_printf("(NULL)\n");
}

static void	print_assignment_array(char *assignment_array[])
{
	int	i;

	i = 0;
	ft_printf("assignment_array: ");
	while (assignment_array && assignment_array[i])
	{
		ft_printf("%s -> ", assignment_array[i]);
		i++;
	}
	ft_printf("(NULL)\n");
}
