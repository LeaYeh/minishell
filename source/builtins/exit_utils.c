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

bool	is_overflow(char *str)
{
	if ((long long)ft_atof(str) > LLONG_MAX || \
		(long long)ft_atof(str) < LLONG_MIN)
		return (true);
	return (false);
}

int	get_args_error(char **args)
{
	int	type;
	// int	i;

	if (!*args)
		return (NO_ARGS);
	type = NORM_ARGS;
	if (!valid_number(args[0]) || is_overflow(args[0]))
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
