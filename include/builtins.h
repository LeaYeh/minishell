/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:22:38 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/10 18:24:16 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "defines.h"

typedef enum e_exit_args_error
{
	NO_ARGS = -1,
	NORM_ARGS = 0,
	TOO_MANY_ARGS,
	NOT_NUMERIC,
}	t_exit_args_error;

int		ft_exec_env(t_shell *shell);
int		ft_exec_echo(char **args);
int		ft_exec_pwd(void);
void	exec_exit(t_shell *shell, t_final_cmd_table *final_cmd_table);

int		get_args_error(char **args);

#endif
