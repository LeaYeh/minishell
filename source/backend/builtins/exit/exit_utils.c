/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:30 by lyeh              #+#    #+#             */
/*   Updated: 2024/05/21 15:05:47 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static bool	valid_number(char *str);

t_exit_err	get_args_error(char *args[])
{
	t_exit_err	error_type;

	if (!args || !args[1])
		return (EX_NO_ARGS);
	error_type = EX_NORM_ARGS;
	if (!valid_number(args[1]) || ft_isoverflow_long(args[1]))
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
	if (ft_issign(str[i]))
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
