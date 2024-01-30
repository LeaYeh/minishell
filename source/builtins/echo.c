#include "defines.h"
#include "utils.h"

bool	is_newline_option(char *str)
{
	if (str && ft_strcmp(str, "-n") == 0)
		return (true);
	return (false);
}

// TODO: printf without newline will not flash the buffer in time
// but ft_printf is not thread safe
int	ft_exec_echo(char **args)
{
	int		i;
	bool	end_with_newline;

	i = 1;
	if (is_newline_option(args[i]))
	{
		end_with_newline = false;
		i++;
	}
	else
		end_with_newline = true;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[++i])
			ft_printf(" ");
	}
	if (end_with_newline)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
