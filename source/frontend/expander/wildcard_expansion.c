/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:47:40 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/28 23:18:33 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	set_file_list(t_list **file_list)
{
	DIR				*dir;
	struct dirent	*file;
	char			*filename;

	dir = opendir(".");
	if (dir == NULL)
		return (true);
	file = readdir(dir);
	while (file != NULL)
	{
		filename = ft_strdup(file->d_name);
		if (!filename)
			break ;
		if (!ft_lstnew_front(file_list, filename))
			break ;
		file = readdir(dir);
	}
	if (errno != SUCCESS)
	{
		perror(PROGRAM_NAME": ");
		return (closedir(dir), false);
	}
	return (closedir(dir), true);
}

bool	ascending(const char *str1, const char *str2)
{
	return (ft_strcmp(str1, str2) <= 0);
}

bool	alphabetic(const char *str1, const char *str2)
{
	while (!isalnum(*str1) && *str1)
		str1++;
	while (!isalnum(*str2) && *str2)
		str2++;
	if (isdigit(*str1) && isalpha(*str2))
		return (true);
	if (isalpha(*str1) && isdigit(*str2))
		return (false);
	if (isdigit(*str1) && isdigit(*str2))
		return (*str1 <= *str2);
	if (isalpha(*str1) && isalpha(*str2))
	{
		if (tolower(*str1) == tolower(*str2))
			return (*str1 <= *str2);
		else
			return (tolower(*str1) <= tolower(*str2));
	}
	return (*str1 <= *str2);
}

void	sort_file_list(t_list **file_list)
{
	ft_lstsort_merge(file_list, (void *)alphabetic);
}

void	skip_wildcard(char **filename, char **word)
{
	char	backup;
	char	*tmp;

	while (**word == '*')
		(*word)++;
	tmp = ft_strchr(*word, '*');
	if (tmp)
	{
		backup = *tmp;
		*tmp = '\0';
		*filename = ft_strnstr(*filename, *word, ft_strlen(*filename));
		*tmp = backup;
	}
	else
		*filename = ft_strrnstr(*filename, *word, ft_strlen(*filename));
}

bool	match_filename(char *filename, char *word)
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
		if (*word == '*')
			skip_wildcard(&filename, &word);
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
	while (*word == '*')
		word++;
	return (!*filename && !*word);
}


bool	expand_wildcard(t_list **tmp_lst, char *word, t_list *file_list)
{
	char	*dup;

	while (file_list)
	{
		if (match_filename(file_list->content, word))
		{
			dup = ft_strdup(file_list->content);
			if (!dup)
				return (false);
			if (!ft_lstnew_back(tmp_lst, dup))
				return (free(dup), false);
		}
		file_list = file_list->next;
	}
	return (true);
}

static bool	iter_word_list(t_list **lst, t_list *file_list)
{
	t_list	*cur;
	t_list	*tmp_lst;
	char	*word;

	cur = *lst;
	while (cur)
	{
		word = cur->content;
		if (ft_strchr(word, '*'))
		{
			tmp_lst = NULL;
			if (!expand_wildcard(&tmp_lst, word, file_list))
				return (ft_lstclear(&tmp_lst, free), false);
			if (tmp_lst)
			{
				ft_lstdrop_node(lst, &cur, free);
				ft_lstinsert_before(lst, cur, tmp_lst);
				continue ;
			}
		}
		cur = cur->next;
	}
	return (true);
}

bool	handle_wildcard_expansion(t_list **lst)
{
	t_list	*file_list;

	file_list = NULL;
	set_file_list(&file_list);
	sort_file_list(&file_list);
	if (!iter_word_list(lst, file_list))
		return (ft_lstclear(&file_list, free), false);
	ft_lstclear(&file_list, free);
	return (true);
}
