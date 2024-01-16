/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:59:15 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/14 20:23:12 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

// after expander if cmd_name => NULL, the cmd_name should be replace by the first non-null argument
// 	cmd_args need to filter out the NULL
// => Maybe combine the cmd_name and cmd_args into one list in a function and pass to expander 1-1 then separate back
// if the executor receives "1 2 3" as cmd_name, it should be split into "1" "2" "3"

char	**combine_cmd_info(char *cmd_name, char **cmd_args)
{
	char	**cmd_info_array;
	int		i;

	cmd_info_array = ft_calloc(get_array_len(cmd_args) + 2, sizeof(char *));
	if (!cmd_info_array)
		return (NULL);
	cmd_info_array[0] = ft_strdup(cmd_name);
	if (!cmd_info_array[0])
		return (free(cmd_info_array), NULL);
	i = 0;
	while (cmd_args[i])
	{
		cmd_info_array[i + 1] = ft_strdup(cmd_args[i]);
		if (!cmd_info_array[i + 1])
			return (free_array(cmd_info_array), NULL);
		i++;
	}
}

void	handle_expand_error(t_shell *shell, char *string, t_list **expanded_list)
{
	if (!string)
		shell->exit_code = GENERAL_ERROR;
	else
		shell->exit_code = EXPAND_ERROR;
	ft_lstclear(expanded_list, free);
}

bool	expand_cmd_info(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	char	**cmd_info_array;
	t_list	*expanded_list;
	int		i;

	cmd_info_array = combine_cmd_info(
		final_cmd_table->cmd_name, final_cmd_table->cmd_args);
	if (!cmd_info_array)
		return (false);
	i = 0;
	while (cmd_info_array[i])
	{
		if (!ft_expander(cmd_info_array[i], &expanded_list, shell))
			return (free_array(cmd_info_array), false);
		i++;
	}
	return (free_array(cmd_info_array), true);
}

// if true...
// 		string=string, *list = one element list (except wildcard)
// if false...
// 		general error, string=NULL, *list = NULL
// 		expander error, string=string, *list = NULL
bool    handle_expansion(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	if (!expand_cmd_info(shell, final_cmd_table))
		return (false);
	return (true);
}
