/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:04:52 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/30 19:51:35 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "debug.h"

bool	ft_execute(t_shell *shell)
{
	if (!ft_heredoc(shell->cmd_table_list))
		return (false);
	return (true);
}
