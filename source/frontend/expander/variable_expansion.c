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

static bool	split_words(t_list **lst, char **new_str, t_expander_task *task);

bool	expand_variable(t_list **lst, char **new_str, t_expander_task *task, t_list *env_list)
{
	char	*value;

	value = get_value_from_env_list(env_list, task->varname);
	if (!value)
		value = "";
	task->result_len = ft_strlen(value);
	if (!ft_strrplc_part(new_str, value, task->start, task->replace_len))
		return (false);
	if (task->type != ET_VAR_NO_SPLIT)
		return (split_words(lst, new_str, task->start, task->result_len));
	return (true);
}

// Search from the back
static bool	split_words(t_list **lst, char **new_str, size_t start, size_t len)
{
	char	*words[2];
	char	*tmp;


	words = ft_split_at_index(*new_str, )
}

// static bool	split_words(t_list **lst, char **new_str, t_expander_task *task)
// {
// 	char	*word;
// 	char	*tmp;

// 	word = ft_strtok(*new_str, " \t\n");
// 	while (word)
// 	{
// 		tmp = ft_strdup(word);
// 		if (!tmp)
// 			return (false);
// 		if (!ft_lstnew_back(lst, tmp))
// 			return (free(tmp), false);
// 		word = ft_strtok(NULL, " \t\n");
// 	}
// 	ft_free_and_null((void **)new_str);
// 	return (true);
// }
