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

static int	get_open_pair_index(unsigned char c, t_is_open_pair_op operation)
{
	if (operation == OP_CLEAN)
		return (0);
	if (c == '\'')
		return (0);
	if (c == '"')
		return (1);
	return (-1);
}

bool	is_open_pair(unsigned char c, t_is_open_pair_op operation)
{
	static bool	status[2];
	int			i;

	if (c == 0 && operation == OP_GET)
		return (status[0] || status[1]);
	i = get_open_pair_index(c, operation);
	if (i == -1)
		return (false);
	if (operation == OP_GET)
		return (status[i]);
	else if (operation == OP_SET)
		status[i] ^= true;
	else if (operation == OP_RESET)
		status[i] = false;
	else if (operation == OP_CLEAN)
		while (i < 2)
			status[i++] = false;
	return (status[i]);
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

bool	skip_dollar_brace(char *str, size_t *i, bool is_in_dquote)
{
	size_t	start;

	start = *i;
	while (str[(*i)++])
	{
		if (str[*i] == '\'' && !is_in_dquote)
		{
			if (!skip_single_quote(str, i))
				return (false);
		}
		else if (str[*i] == '"')
		{
			if (!skip_double_quote(str, i))
				return (false);
		}
		else if (ft_strncmp(&str[*i], DOLLAR_BRACE, 2) == 0)
		{
			if (!skip_dollar_brace(str, i, is_in_dquote))
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

	if (is_open_pair('\'', OP_GET))
		return (false);
	start = *i;
	while (str[(*i)++])
	{
		if (str[*i] == '\'')
			return (true);
	}
	*i = start;
	return (false);
}

int	get_list_strlen(t_list *list, char *delim)
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
