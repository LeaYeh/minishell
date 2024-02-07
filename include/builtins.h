/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:22:38 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/17 10:55:28 by ldulling         ###   ########.fr       */
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

int		ft_exec_env(char **envp);
int		ft_exec_echo(char **args);
int		ft_exec_pwd(void);
void	exec_exit(t_shell *shell);
int		exec_cd(char **args, t_list **env_list);

int		get_args_error(char **args);

#endif
