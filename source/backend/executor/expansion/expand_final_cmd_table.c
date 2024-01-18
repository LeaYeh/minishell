/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_final_cmd_table.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:59:15 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/18 23:20:28 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "executor.h"
#include "expander.h"
#include "utils.h"

int	expand_array(t_shell *shell, char ***array)
{
	t_list	*expanded_list;
	int		i;
	int		ret;

	expanded_list = NULL;
	i = 0;
	while ((*array)[i])
	{
		ret = ft_expander((*array)[i], &expanded_list, shell);
		if (ret != SUCCESS)
			return (ft_lstclear(&expanded_list, free), ret);
		i++;
	}
	free_array(array);
	*array = convert_list_to_string_array(expanded_list);
	ft_lstclear(&expanded_list, free);
	if (!*array)
		return (GENERAL_ERROR);
	return (SUCCESS);
}

bool	expand_simple_cmd(
	t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	int		ret;

	ret = expand_array(shell, &final_cmd_table->simple_cmd);
	if (ret == GENERAL_ERROR)
		return (false);
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
	// TODO: Still need to handle impact of expander error on process execution
	if (!expand_simple_cmd(shell, final_cmd_table))
		return (false);
	return (true);
}
