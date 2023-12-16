/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:07:52 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/16 17:41:52 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "clean.h"

bool	check_env_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		return (false);
	}
	return (true);
}

bool	exec_env(t_shell *shell, char **args)
{
	t_list	*curr;
	t_env	*env;

	if (!check_env_args(args))
		return (false);
	curr = shell->env_list;
	while (curr)
	{
		env = (t_env *)curr->content;
		ft_printf("%s=%s\n", env->key, env->value);
		curr = curr->next;
	}
	return (true);
}

void	free_str_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
}

void	ft_exec_env(t_shell *shell, char **args)
{
	if (!exec_env(shell, args))
	{
		free_str_array(args);
		shell->exit_code = EXIT_FAILED;
		ft_clean_shell(shell);
	}
	else
		free_str_array(args);
}
