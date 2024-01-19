#include "builtins.h"
#include "utils.h"
#include "clean.h"

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
	while (str[i])
	{
		if (ft_isdigit(str[i]) || \
			(ft_strlen(str) > 1 && i == 0 && is_sign(str[i])))
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
	int	i;

	if (!args)
		return (NO_ARGS);
	type = NORM_ARGS;
	if (!valid_number(args[0]) || is_overflow(args[0]))
		type = NOT_NUMERIC;
	if (get_array_len(args) > 1)
	{
		type = TOO_MANY_ARGS;
		i = 1;
		while (args[i])
		{
			if (!valid_number(args[i]) || is_overflow(args[i]))
			{
				type = NOT_NUMERIC;
				break ;
			}
			i++;
		}
	}
	return (type);
}

void	exec_exit(t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	int		args_error;
	int		exit_code;
	char	**args;

	args = final_cmd_table->cmd_args;
	args_error = get_args_error(args);
	if (args_error == NORM_ARGS)
		exit_code = ((long long)ft_atof(args[0])) % 256;
	else
		exit_code = args_error;
	printf("args_error: %d\n", args_error);
	printf("exit_code: %d\n", exit_code);
	printf("exit\n");
	if (args_error != TOO_MANY_ARGS)
	{
		if (args_error == NOT_NUMERIC)
			ft_dprintf(2,
				ERROR_EXIT_NUMERIC_ARG, PROGRAM_NAME, "exit", args[0]);
		free_final_cmd_table(&final_cmd_table);
		ft_clean_and_exit_shell(shell, exit_code, "triggered exit");
	}
	else
		ft_dprintf(2, ERROR_EXIT_TOO_MANY_ARGS, PROGRAM_NAME, "exit");
}
