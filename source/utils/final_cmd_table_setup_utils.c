/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_table_setup_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:04:37 by lyeh              #+#    #+#             */
/*   Updated: 2024/02/18 00:04:38 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "expander.h"

bool	expand_simple_cmd(t_shell *shell, t_list *simple_cmd_list)
{
	t_list		*expanded_list;
	int			ret;

	expanded_list = NULL;
	ret = expand_list(shell, simple_cmd_list, &expanded_list,
			E_EXPAND | E_SPLIT_WORDS | E_RM_QUOTES);
	if (ret == MALLOC_ERROR)
		return (ft_lstclear(&expanded_list, free), false);
	else if (ret == BAD_SUBSTITUTION)
		ft_lstclear(&expanded_list, free);
	shell->final_cmd_table->simple_cmd = \
		convert_list_to_string_array(expanded_list);
	ft_lstclear(&expanded_list, free);
	if (!shell->final_cmd_table->simple_cmd)
		return (false);
	return (true);
}

int	get_env_size(t_list *env_list)
{
	t_env	*env_node;
	int		size;

	size = 0;
	while (env_list)
	{
		env_node = (t_env *)env_list->content;
		if (env_node->export && env_node->value)
			size++;
		env_list = env_list->next;
	}
	return (size);
}
