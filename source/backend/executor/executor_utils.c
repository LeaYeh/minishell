/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:37:47 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/19 14:39:54 by lyeh             ###   ########.fr       */
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
		raise_error_to_own_subprocess(shell, MALLOC_ERROR, MALLOC_FMSG);
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
