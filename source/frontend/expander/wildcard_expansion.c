/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:47:40 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/27 13:27:18 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

#include "debug.h"

void	print_list(t_list *list)
{
	while (list)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
}

bool	set_file_list(t_list **file_list)
{
	DIR				*dir;
	struct dirent	*file;
	char			*filename;

	// (void)str;

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
		perror(NULL);
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
	// printf("\n------before sort------\n");
	// print_list(*file_list);
	ft_lstsort_merge(file_list, (void *)alphabetic);
	// printf("\n------after sort------\n");
	// print_list(*file_list);
}

bool	match_filename(char *filename, const char *word)
{
	int	i;
	int	j;
	int	k;

	if (*filename == '.')	// Not so easy...
	{
		if (*word != '.')
			return (false);
		filename++;
		word++;
	}
	k = 1;
	while (*filename)
	{
		i = 0;
		j = 0;
		while (filename[i] && word[j])
		{
			if (word[j] == '*')
			{
				while (word[j] == '*')
					j++;
				while (filename[i] && filename[i] != word[j])
					i++;
			}
			else if (filename[i] == word[j])
			{
				i++;
				j++;
			}
			else
			{
				filename = &filename[k];
				j = 0;
				continue;
			}
		}
		while (word[j] == '*')
			j++;
		if (filename[i] || word[j])
		{
			filename = &filename[k];
			continue;
		}
		return (true);
	}
	return (false);
}


bool	expand_wildcard(t_list **tmp_lst, char *word, t_list *file_list)
{
	char	*tmp;

	while (file_list)
	{
		if (match_filename(file_list->content, word))
		{
			tmp = ft_strdup(file_list->content);
			if (!tmp)
				return (false);
			if (!ft_lstnew_back(tmp_lst, tmp))
				return (free(tmp), false);
		}
		file_list = file_list->next;
	}
	return (true);
}

bool	go_through_list(t_list **lst, t_list *file_list)
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

	(void)lst;
	file_list = NULL;
	set_file_list(&file_list);

	sort_file_list(&file_list);

	if (!go_through_list(lst, file_list))
		return (ft_lstclear(&file_list, free), false);

	ft_lstclear(&file_list, free);
	return (true);
}
