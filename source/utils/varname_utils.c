/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varname_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:12:16 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/30 12:02:11 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

char	*get_varname(char *str)
{
	int	varname_len;

	varname_len = get_varname_len(str);
	return (ft_strndup(str, varname_len));
}

int	get_varname_len(char *str)
{
	int	len;

	len = 0;
	while (is_valid_varname_char(str[len]))
		len++;
	return (len);
}
