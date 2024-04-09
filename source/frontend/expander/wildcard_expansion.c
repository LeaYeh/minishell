/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:47:40 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/01 02:03:18 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static bool	iter_word_list(
				t_list **expanded_list, t_list *file_list, t_list **task_list);
static bool	match_filename(char *filename, char *word, t_list *task_list);
static bool	expand_wildcard(
				t_list **tmp_lst,
				char *word,
				t_list *file_list,
				t_list *task_list);

bool	handle_wildcard_expansion(
			t_list **expanded_list, t_list **task_list)
{
	t_list	*file_list;

	if (!any_task_of_type(*task_list, ET_WILDCARD))
		return (true);
	file_list = NULL;
	if (!set_file_list(&file_list))
		return (ft_lstclear(&file_list, free), false);
	sort_file_list(&file_list);
	if (!iter_word_list(expanded_list, file_list, task_list))
		return (ft_lstclear(&file_list, free), false);
	ft_lstclear(&file_list, free);
	return (true);
}

static bool	iter_word_list(
				t_list **expanded_list, t_list *file_list, t_list **task_list)
{
	t_list	*cur;
	t_list	*tmp_lst;
	char	*word;

	cur = *expanded_list;
	while (cur)
	{
		word = cur->content;
		if (get_next_wildcard(word, *task_list))
		{
			tmp_lst = NULL;
			if (!expand_wildcard(&tmp_lst, word, file_list, *task_list))
				return (ft_lstclear(&tmp_lst, free), false);
			drop_task_types(task_list, (char **)&cur->content, ET_WILDCARD);
			if (tmp_lst)
			{
				ft_lstdrop_node(expanded_list, &cur, free);
				ft_lstinsert_before(expanded_list, cur, tmp_lst);
				continue ;
			}
		}
		cur = cur->next;
	}
	return (true);
}

static bool	match_filename(char *filename, char *word, t_list *task_list)
{
	if (*filename == '.')
	{
		if (*word != '.')
			return (false);
		filename++;
		word++;
	}
	while (filename && *filename && *word)
	{
		if (is_wildcard(word, task_list))
			skip_wildcard(&filename, &word, task_list);
		else if (*filename == *word)
		{
			filename++;
			word++;
		}
		else
			return (false);
	}
	if (!filename)
		return (!*word);
	while (is_wildcard(word, task_list))
		word++;
	return (!*filename && !*word);
}

static bool	expand_wildcard(
				t_list **tmp_lst,
				char *word,
				t_list *file_list,
				t_list *task_list)
{
	char	*dup;

	while (file_list)
	{
		if (match_filename(file_list->content, word, task_list))
		{
			dup = ft_strdup(file_list->content);
			if (!dup || !ft_lstnew_back(tmp_lst, dup))
				return (free(dup), false);
		}
		file_list = file_list->next;
	}
	return (true);
}
