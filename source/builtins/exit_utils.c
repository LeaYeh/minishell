#include "defines.h"
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

	if (!str)
		return (false);
	i = 0;
	if (ft_strlen(str) > 1 && is_sign(str[i]))
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

int	get_args_error(char **args)
{
	int	type;
	// int	i;

	if (!*args)
		return (NO_ARGS);
	type = NORM_ARGS;
	if (!valid_number(args[0]) || is_atol_overflow(args[0]))
		type = NOT_NUMERIC;
	else if (get_array_len(args) > 1)
	{
		type = TOO_MANY_ARGS;
		// i = 1;
		// while (args[i])
		// {
		// 	if (!valid_number(args[i]) || is_overflow(args[i]))
		// 	{
		// 		type = NOT_NUMERIC;
		// 		break ;
		// 	}
		// 	i++;
		// }
	}
	return (type);
}
