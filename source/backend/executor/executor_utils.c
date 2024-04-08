/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:15:37 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/04 22:45:47 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean.h"
#include "signals.h"
#include "utils.h"

int	set_expanded_cmd_name(
		char **cmd_name, t_sh *shell, t_list *simple_cmd_list)
{
	t_list	*expanded_list;
	int		ret;

	expanded_list = NULL;
	ret = expand_list(shell, simple_cmd_list, &expanded_list, \
			E_PARAM | E_SPLIT_WORDS | E_WILDCARD | E_RM_QUOTES);
	*cmd_name = ft_lstpop_front_content(&expanded_list);
	ft_lstclear(&expanded_list, free);
	return (ret);
}

void	handle_expansion_error(t_sh *shell, t_list_d **cmd_table_node, int ret)
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
			clean_and_exit_shell(shell, shell->exit_code, NULL);
		*cmd_table_node = NULL;
	}
}
