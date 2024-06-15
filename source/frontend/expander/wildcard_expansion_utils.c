/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:03:50 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/01 02:02:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	is_wildcard(char *word, t_list *task_list)
{
	t_expd_tsk	*task;

	while (task_list)
	{
		task = task_list->content;
		if (task->type == ET_WILDCARD)
		{
			if (*word == '*' && word >= *task->base_str + task->start && \
				word < *task->base_str + task->start + task->replace_len)
				return (true);
		}
		task_list = task_list->next;
	}
	return (false);
}

char	*get_next_wildcard(char *word, t_list *task_list)
{
	char	*asterisk;

	asterisk = ft_strchr(word, '*');
	while (asterisk)
	{
		if (is_wildcard(asterisk, task_list))
			break ;
		asterisk = ft_strchr(asterisk + 1, '*');
	}
	return (asterisk);
}

void	skip_wildcard(char **filename, char **word, t_list *task_list)
{
	char	*asterisk;
	char	backup;

	while (is_wildcard(*word, task_list))
		(*word)++;
	asterisk = get_next_wildcard(*word, task_list);
	if (asterisk)
	{
		backup = *asterisk;
		*asterisk = '\0';
		*filename = ft_strnstr(*filename, *word, ft_strlen(*filename));
		*asterisk = backup;
	}
	else
		*filename = ft_strrnstr(*filename, *word, ft_strlen(*filename));
}
