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
	size_t	offset;
	char	tmp;
	char	*value;
	char	*varname;
	size_t	varname_len;

	offset = get_offset(&(*new_str)[task->start]);
	varname = &(*new_str)[task->start + offset];
	varname_len = get_varname_len(varname);
	tmp = varname[varname_len];
	varname[varname_len] = '\0';
	value = get_value_from_env_list(env_list, varname);
	if (!value)
		value = "";
	varname[varname_len] = tmp;
	if (!ft_strrplc_part(new_str, value, task->start, task->len))
		return (false);
	return (true);
}

size_t	get_varname_len(char *str)
{
	size_t	len;

	len = 0;
	while (is_valid_varname_char(str[len]))
		len++;
	return (len);
}
