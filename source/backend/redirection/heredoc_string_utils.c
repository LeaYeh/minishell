/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_string_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:50:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/04 23:25:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

static int	get_list_strlen(t_list *list, char *delim);

bool	is_str_quoted(char *str)
{
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		return (true);
	return (false);
}

char	*concat_list_to_string(t_list *list, char *delim)
{
	char	*str;
	int		cur_len;
	int		delim_len;

	str = (char *)ft_calloc(get_list_strlen(list, delim) + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (delim)
		delim_len = ft_strlen(delim);
	cur_len = 0;
	while (list)
	{
		if (list->content)
			cur_len += ft_snprintf(&str[cur_len],
					ft_strlen(list->content) + 1, "%s", list->content);
		if (delim)
			cur_len += ft_snprintf(&str[cur_len], delim_len + 1, "%s", delim);
		list = list->next;
	}
	return (str);
}

static int	get_list_strlen(t_list *list, char *delim)
{
	int		total_length;
	t_list	*node;

	total_length = 0;
	node = list;
	while (node)
	{
		if (node->content)
			total_length += ft_strlen(node->content);
		total_length += ft_strlen(delim);
		node = node->next;
	}
	return (total_length);
}
