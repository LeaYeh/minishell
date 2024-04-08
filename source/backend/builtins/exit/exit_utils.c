/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:30 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/20 00:36:35 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"

static bool	valid_number(char *str);
static bool	is_sign(char c);
static bool	is_atol_overflow(char *str);

t_exit_err	get_args_error(char *args[])
{
	t_exit_err	error_type;

	if (!args || !args[1])
		return (EX_NO_ARGS);
	error_type = EX_NORM_ARGS;
	if (!valid_number(args[1]) || is_atol_overflow(args[1]))
		error_type = EX_NOT_NUMERIC;
	else if (args[2])
		error_type = EX_TOO_MANY_ARGS;
	return (error_type);
}

static bool	valid_number(char *str)
{
	int	i;

	if (!*str)
		return (false);
	i = 0;
	while (str[i] && ft_strchr(WHITESPACE, str[i]))
		i++;
	if (is_sign(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (false);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			break ;
	}
	while (str[i] && ft_strchr(WHITESPACE, str[i]))
		i++;
	if (str[i])
		return (false);
	return (true);
}

static bool	is_sign(char c)
{
	if (c == '+' || c == '-')
		return (true);
	return (false);
}

static bool	is_atol_overflow(char *str)
{
	int		i;
	char	*long_max;
	int		num_len;

	i = 0;
	while (str[i] && ft_strchr(WHITESPACE, str[i]))
		i++;
	if (str[i] == '-')
		long_max = "9223372036854775808";
	else
		long_max = "9223372036854775807";
	if (is_sign(str[i]))
		i++;
	while (str[i] == '0')
		i++;
	num_len = 0;
	while (ft_isdigit(str[i + num_len]))
		num_len++;
	if (num_len > (int)ft_strlen(long_max) || \
		ft_strncmp(&str[i], long_max, num_len) > 0)
		return (true);
	return (false);
}
