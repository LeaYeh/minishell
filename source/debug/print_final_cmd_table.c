/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_final_cmd_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:17:36 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/11 21:21:18 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
// #include "utils.h"

void	print_cmd_args_array(char **cmd_args)
{
	int	i;

	i = 0;
	printf("cmd_args: ");
	while (cmd_args && cmd_args[i])
	{
		printf("%s -> ", cmd_args[i]);
		i++;
	}
	printf("(NULL)\n");
}

void	print_assignment_array(char **assignment_array)
{
	int	i;

	i = 0;
	printf("assignment_array: ");
	while (assignment_array && assignment_array[i])
	{
		printf("%s -> ", assignment_array[i]);
		i++;
	}
	printf("(NULL)\n");
}

void	print_final_cmd_table(t_final_cmd_table *final_cmd_table)
{
	printf("\n\n========= final cmd table =========\n");
	printf("cmd_name: %s\n", final_cmd_table->cmd_name);
	print_cmd_args_array(final_cmd_table->cmd_args);
	print_assignment_array(final_cmd_table->assignment_array);
	printf("===================================\n\n");
}
