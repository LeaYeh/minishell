/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:02 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 17:40:04 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	is_newline_option(char *args[], int *i)
{
	int	j;

	while (args[*i] && ft_strncmp(args[*i], "-n", 2) == 0)
	{
		j = 2;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] != '\0')
			break ;
		(*i)++;
	}
	if (*i > 1)
		return (true);
	return (false);
}

int	get_combined_args_len(char *args[], bool end_with_newline)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (args[i])
	{
		len += ft_strlen(args[i]);
		if (args[++i])
			len++;
	}
	if (end_with_newline)
		len++;
	return (len);
}

char	*combine_args(char *args[], bool end_with_newline)
{
	int		i;
	char	*str;
	int		cur_len;
	int		arg_len;

	str = ft_calloc(
			get_combined_args_len(args, end_with_newline) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	cur_len = 0;
	while (args[i])
	{
		arg_len = ft_strlen(args[i]);
		if (i == 0)
			cur_len += ft_snprintf(&str[cur_len], arg_len + 1, "%s", args[i]);
		else
			cur_len += ft_snprintf(&str[cur_len], arg_len + 2, " %s", args[i]);
		i++;
	}
	if (end_with_newline)
		ft_snprintf(&str[cur_len], 2, "\n");
	return (str);
}

int	exec_echo(char *args[])
{
	int		i;
	bool	end_with_newline;
	char	*combined_str;

	i = 1;
	if (is_newline_option(args, &i))
		end_with_newline = false;
	else
		end_with_newline = true;
	combined_str = combine_args(args + i, end_with_newline);
	if (!combined_str)
		return (MALLOC_ERROR);
	ft_printf("%s", combined_str);
	free(combined_str);
	return (EXIT_SUCCESS);
}
