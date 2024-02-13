/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:50:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/03 14:28:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	replace_string_content(char **str, char *new_content)
{
	char	*tmp;

	tmp = ft_strdup(new_content);
	if (!tmp)
		return (false);
	free(*str);
	*str = tmp;
	return (true);
}

bool	is_valid_varname(char *str)
{
	int	i;

	i = 0;
	if (!str || !is_valid_varname_start(str[i]))
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!is_valid_varname_char(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_varname_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_valid_varname_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	skip_to_same_quote(char *str, size_t *i)
{
	char	*open_quote;

	open_quote = ft_strchr(QUOTES, str[*i]);
	if (!open_quote)
		return (true);
	while (str[*i])
	{
		(*i)++;
		if (str[*i] == *open_quote)
			return (true);
	}
	return (false);
}

bool	skip_dollar_brace(char *str, size_t *i, bool is_in_dquote)
{
	size_t	start;

	start = *i;
	while (str[(*i)++])
	{
		if (ft_strncmp(&str[*i], DOLLAR_BRACE, 2) == 0)
		{
			if (!skip_dollar_brace(str, i, is_in_dquote))
				return (false);
		}
		else if (str[*i] == '"')
		{
			if (!skip_double_quote(str, i))
				return (false);
		}
		else if (str[*i] == '\'' && !is_in_dquote)
		{
			if (!skip_single_quote(str, i))
				return (false);
		}
		else if (str[*i] == CLOSING_BRACE)
			return (true);
	}
	*i = start;
	return (false);
}

bool	skip_double_quote(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[(*i)++])
	{
		if (ft_strncmp(&str[*i], DOLLAR_BRACE, 2) == 0)
		{
			if (!skip_dollar_brace(str, i, true))
				return (false);
		}
		else if (str[*i] == '"')
			return (true);
	}
	*i = start;
	return (false);
}

bool	skip_single_quote(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[(*i)++])
	{
		if (str[*i] == '\'')
			return (true);
	}
	*i = start;
	return (false);
}

int	count_total_strlen(t_list *list, char *delim)
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

char	*concat_list_to_string(t_list *list, char *delim)
{
	char	*str;
	int		cur_len;
	int		delim_len;

	str = (char *)ft_calloc(count_total_strlen(list, delim) + 1, sizeof(char));
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
