#include "defines.h"
#include "utils.h"

bool	is_newline_option(char *str)
{
	if (str && ft_strcmp(str, "-n") == 0)
		return (true);
	return (false);
}

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
		printf("%s", args[i]);
		if (args[++i])
			printf(" ");
	}
	if (end_with_newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
