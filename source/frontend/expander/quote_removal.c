/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:09:34 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/28 02:12:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	remove_quote(char **new_str, t_list *task_list)
{
	t_expander_task	*task;

	task = task_list->content;
	if (!ft_strrplc_part(new_str, "", task->start, task->replace_len))
		return (false);
	task->result_len = 0;
	return (true);
}
