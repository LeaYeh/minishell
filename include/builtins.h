/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:22:38 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/02 22:56:18 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "defines.h"

int			exec_env(char *env[]);
int			exec_echo(char *args[]);
int			exec_pwd(void);
int			exec_cd(char *args[], t_list **env_list);
int			exec_export(char *args[], t_list **env_list);
int			exec_unset(char *args[], t_list **env_list);
void		exec_exit(t_sh *shell, char *args[]);
int			exec_easter_egg(void);

t_exit_err	get_args_error(char *args[]);

#endif
