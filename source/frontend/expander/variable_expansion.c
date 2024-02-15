/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:18:15 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/28 02:12:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

bool	expand_variable(char **new_str, t_expander_task *task, t_list *env_list)
{
	char	*value;

	value = get_value_from_env_list(env_list, task->varname);
	if (!value)
		value = "";
	if (!ft_strrplc_part(new_str, value, task->start, task->replace_len))
		return (false);
	return (true);
}
