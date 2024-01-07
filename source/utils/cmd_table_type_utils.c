/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_type_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:27:56 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/07 15:29:58 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

bool	is_control_op_cmd_table(int cmd_table_type)
{
	return (cmd_table_type == C_AND || cmd_table_type == C_OR || \
		cmd_table_type == C_PIPE);
}
