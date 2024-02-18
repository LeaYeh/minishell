/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varname_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:12:16 by lyeh              #+#    #+#             */
/*   Updated: 2024/02/18 00:12:17 by lyeh             ###   ########.fr       */
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
