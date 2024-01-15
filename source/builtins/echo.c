#include "defines.h"
#include "utils.h"

bool	is_newline_option(char *str)
{
	if (str && ft_strlen(str) == 2 && str[0] == '-' && str[1] == 'n')
		return (true);
	return (false);
}

int	ft_exec_echo(char **args)
{
	int		i;
	bool	end_with_newline;

	if (get_array_len(args) == 0)
		return (printf("\n"), EXIT_SUCCESS);
	end_with_newline = true;
	i = 0;
	while (args[i])
	{
		if (i == 0 && is_newline_option(args[i]))
		{
			end_with_newline = false;
			i++;
			continue ;
		}
		if ((end_with_newline && i != 0) || (!end_with_newline && i != 1))
			printf(" ");
		printf("%s", args[i++]);
	}
	if (end_with_newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
