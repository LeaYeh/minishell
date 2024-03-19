/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:30 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 17:40:31 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"

bool	is_sign(char c)
{
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

bool	valid_number(char *str)
{
	int	i;

	if (!*str)
		return (false);
	i = 0;
	if (is_sign(str[i]))
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (false);
	}
	return (true);
}

bool	is_atol_overflow(char *str)
{
	int		i;
	char	*long_max;

	i = 0;
	if (str[i] == '-')
		long_max = "9223372036854775808";
	else
		long_max = "9223372036854775807";
	if (is_sign(str[i]))
		i++;
	while (str[i] == '0')
		i++;
	if (ft_strlen(&str[i]) < ft_strlen(long_max) || \
		ft_strcmp(&str[i], long_max) <= 0)
		return (false);
	return (true);
}

int	get_args_error(char *args[])
{
	int	type;

	if (!args[1])
		return (EX_NO_ARGS);
	type = EX_NORM_ARGS;
	if (!valid_number(args[1]) || is_atol_overflow(args[1]))
		type = EX_NOT_NUMERIC;
	else if (args[2])
		type = EX_TOO_MANY_ARGS;
	return (type);
}
