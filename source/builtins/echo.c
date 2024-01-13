#include "defines.h"
#include "utils.h"

bool	is_newline_option(char *str)
{
	if (str && ft_strlen(str) == 2 && str[0] == '-' && str[1] == 'n')
		return (true);
	return (false);
}

void	echo_string(char *str, bool end_with_newline)
{
	if (end_with_newline)
		printf("%s\n", str);
	else
		printf("%s", str);
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
		if (is_newline_option(args[i]))
		{
			end_with_newline = false;
			i++;
			continue;
		}
		echo_string(args[i++], end_with_newline);
	}
	return (EXIT_SUCCESS);
}
