/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varname_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:12:16 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/04 23:36:44 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	get_varname_len(char *str);

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

bool	is_valid_varname_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_valid_varname_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_varname(char *str)
{
	int	varname_len;

	varname_len = get_varname_len(str);
	return (ft_strndup(str, varname_len));
}

static int	get_varname_len(char *str)
{
	int	len;

	len = 0;
	while (is_valid_varname_char(str[len]))
		len++;
	return (len);
}
