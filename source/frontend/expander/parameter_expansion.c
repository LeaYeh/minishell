/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 00:34:37 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/03 01:42:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

// Currently removes the dollar sign for this test case: $"$$$$'
// It better shouldn't.
// TODO We have have to check for unclosed quotes somewhere
bool	handle_dollar_quotes(char **str, size_t *i)
{
	if (!is_open_pair('"', GET))
		return (replace_part_of_str(str, "", *i, 1));
	else
		(*i)++;
	return (true);
}

void	skip_to_dollar_not_in_single_quotes(char *str, size_t *i)
{
	while (str[*i])
	{
		if (str[*i] == '$')
			return ;
		else if (str[*i] == '"')
			is_open_pair('"', TOGGLE);
		else if (str[*i] == '\'' && !is_open_pair('"', GET))
			if (!skip_to_same_quote(str, i))
				return ;
		(*i)++;
	}
}

size_t	count_var_len(char *str)
{
	size_t	len;

	if (*str == '$')
	{
		str++;
		if (*str == OPENING_BRACE)
			str++;
	}
	len = 0;
	while (is_valid_varname(*str))
	{
		len++;
		str++;
	}
	return (len);
}

size_t	count_replace_len(char *str)
{
	size_t	replace_len;

	replace_len = 0;
	if (str[replace_len] == '$')
		replace_len++;
	if (str[replace_len] == OPENING_BRACE)
	{
		while (str[++replace_len] != CLOSING_BRACE)
			;
		replace_len++;
	}
	else if (str[replace_len] == '?')
		replace_len++;
	else
		while (is_valid_varname(str[replace_len]))
			replace_len++;
	return (replace_len);
}

bool	expand_exit_code(char **str, size_t *i, int exit_code)
{
	char	*exit_code_str;
	size_t	replace_len;

	exit_code_str = ft_itoa(exit_code);
	if (!exit_code_str)
		return (false);
	replace_len = count_replace_len(&(*str)[*i]);
	if (!replace_part_of_str(str, exit_code_str, *i, replace_len))
		return (free(exit_code_str), false);
	*i += ft_strlen(exit_code_str);
	return (free(exit_code_str), true);
}

char	*get_replacement(char *var, t_list *env_list)
{
	t_env	*env_node;

	while (env_list)
	{
		env_node = env_list->content;
		if (ft_strcmp(env_node->key, var) == 0)
			return (env_node->value);
		env_list = env_list->next;
	}
	return ("");
}

bool	expand_variable(char **str, size_t *i, size_t offset, t_list *env_list)
{
	size_t	replace_len;
	char	*replacement;
	char	*var;
	size_t	var_len;

	var_len = count_var_len(&(*str)[*i]);
	var = ft_substr(*str, *i + offset, var_len);
	if (!var)
		return (false);
	replace_len = count_replace_len(&(*str)[*i]);
	replacement = get_replacement(var, env_list);
	free(var);
	if (!replace_part_of_str(str, replacement, *i, replace_len))
		return (false);
	*i += ft_strlen(replacement);
	return (true);
}

size_t	count_offset(char *str)
{
	size_t	offset;

	offset = 0;
	if (*str == '$')
	{
		offset++;
		str++;
	}
	if (*str == OPENING_BRACE)
		offset++;
	return (offset);
}

bool	expand_parameter(char **str, size_t *i, t_shell *shell)
{
	size_t	offset;

	offset = count_offset(&(*str)[*i]);
	if ((*str)[*i + offset])
	{
		if ((*str)[*i + offset] == '?')
			return (expand_exit_code(str, i, shell->exit_code));
		else if (is_valid_varname_start((*str)[*i + offset]))
			return (expand_variable(str, i, offset, shell->env_list));
		else if (ft_strchr(QUOTES, (*str)[*i + offset]))
			return (handle_dollar_quotes(str, i));
		*i += offset;
	}
	(*i)++;
	return (true);
}

bool	parameter_expansion(char **str, t_shell *shell)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		skip_to_dollar_not_in_single_quotes(*str, &i);
		if (!(*str)[i])
			break ;
		if (!expand_parameter(str, &i, shell))
			return (false);
	}
	return (true);
}
