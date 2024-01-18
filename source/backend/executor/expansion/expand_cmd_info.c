/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:59:15 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/17 21:37:46 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"

bool	setup_expanded_cmd_name(
	t_final_cmd_table *final_cmd_table, char **expanded_array)
{
	ft_free_and_null((void **)&final_cmd_table->cmd_name);
	if (!expanded_array || !expanded_array[0])
		return (true);
	final_cmd_table->cmd_name = ft_strdup(expanded_array[0]);
	if (!final_cmd_table->cmd_name)
		return (false);
	return (true);
}

bool	setup_expanded_cmd_args(
	t_final_cmd_table *final_cmd_table, char **expanded_array)
{
	int	i;

	free_array(final_cmd_table->cmd_args);
	final_cmd_table->cmd_args = NULL;
	if (!expanded_array || !expanded_array[0])
		return (true);
	i = 1;
	while (expanded_array[i])
	{
		final_cmd_table->cmd_args = append_string_array(
			final_cmd_table->cmd_args, expanded_array[i]);
		if (!final_cmd_table->cmd_args)
			return (false);
		i++;
	}
	return (true);
}

bool	setup_expanded_cmd_info(
	t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	char	**expanded_array;

	expanded_array = NULL;
	shell->exit_code = set_expanded_cmd_info(
			shell, final_cmd_table, &expanded_array);
	if (shell->exit_code == GENERAL_ERROR)
		return (free_array(expanded_array), false);
	if (!setup_expanded_cmd_name(final_cmd_table, expanded_array) || \
		!setup_expanded_cmd_args(final_cmd_table, expanded_array))
	{
		shell->exit_code = GENERAL_ERROR;
		free_array(expanded_array);
		return (false);
	}
	free_array(expanded_array);
	return (true);
}

// if true...
// 		string=string, *list = one element list (except wildcard)
// if false...
// 		general error, string=NULL, *list = NULL
// 		expander error, string=string, *list = NULL
bool	expand_final_cmd_table(
	t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	if (!setup_expanded_cmd_info(shell, final_cmd_table))
		return (false);
	return (true);
}
